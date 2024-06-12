#include "pipex.h"



int	path(char *dest, char *command, size_t dest_size, char **envp)
{
	int		i;
	char	**paths;
	char	*command_path;
	char	*str;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
        i++;
	if (!envp[i] || envp[i][0] != 'P' || envp[i][3] != 'H')
        return (1);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (2);
	i = 0;
	while(paths[i])
	{
		paths[i] = multi_re_strjoin(3, paths[i], "/", command);
		if (!paths[i++])
			return (free_2d_array((void **)paths), 3);
	}
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
			break;
		i++;
	}
	ft_strlcpy(dest, paths[i], dest_size);
	free_2d_array((void **)paths);
	return (0);
}


void	file_to_command(int input_fd, int output_fd, char **command, char **envp)
{
	char	command_path[64];
	char	*temp;

	path(command_path, command[0], 64, envp);
	ft_printf("path: %s\n", command_path);
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	execve(command_path, command, envp);
}

void	command_to_command(int input_fd, int output_fd, char **command, char **envp)
{
	char	command_path[64];
	char	*temp;

	path(command_path, command[0], 64, envp);
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	execve(command_path, command, envp);
}

void	command_to_file(int input_fd, int output_fd, char **command, char **envp)
{
	char	command_path[64];
	char	*temp;

	path(command_path, command[0], 64, envp);
	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	execve(command_path, command, envp);
}
void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			print_err_and_exit(USAGE_BONUS, EXIT_FAILURE);
		data -> limiter = argv[2];
		data -> nb_command = argc - 4;
	}
	else
	{
		if (argc < 5)
			print_err_and_exit(USAGE, EXIT_FAILURE);
		data -> input_file = argv[1];
		data -> nb_command = argc - 3;

	}
	data -> envp = envp;
	data -> output_file = argv[argc - 1];
	data -> previous_pipe = -1;
	data -> pid = malloc(sizeof(int) * (data -> nb_command));
	if (data -> pid == NULL)
		print_err_and_exit(MALLOC_FAILED, EXIT_FAILURE);
}

void	redirect(t_data *data, int j)
{
	int	infile_fd;
	int	outfile_fd;
	close(data->fd[0]);
	if (j == 0)
	{
		infile_fd = open(data -> input_file, O_RDONLY, 0644);
		if (infile_fd == -1)
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			close(infile_fd);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		printf("infile: %d\n", infile_fd);
		close(infile_fd);
		printf("outfile: %d\n", data->fd[1]);
		if (dup2(data -> fd[1], STDOUT_FILENO) == -1)
		{
			close(data -> fd[1]);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(data -> fd[1]);
	}
	else if (j == data->nb_command - 1)
	{
		fprintf(stderr, "Last\n");
		outfile_fd = open(data -> output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			close(outfile_fd);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(outfile_fd);
		fprintf(stderr, "Last ok\n");
	}
	else
	{
		if (dup2(data -> fd[1], STDOUT_FILENO) == -1)
		{
			close (data -> fd[1]);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close (data -> fd[1]);
	}

	if (data -> previous_pipe != -1)
	{
		fprintf(stderr, "previous_pipe: [%d]\n", data->previous_pipe);
		if (dup2(data -> previous_pipe, STDIN_FILENO) == -1)
		{
			close(data -> previous_pipe);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(data -> previous_pipe);
	}
}

void	exec_command(t_data *data, char *cmd, int j)
{
	char	**command;

	command = ft_split(cmd, ' ');
	if (command == NULL)
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
	redirect(data, j);
	execve(command[0], command, data->envp);
	fprintf(stderr, "Failed\n");
	free_and_exit(NULL, EXIT_FAILURE, data, true);
}


void	fork_command(t_data *data, char **argv, int i)
{
	int	j;

	j = 0;
	while (j < data->nb_command)
	{
		if (j != data->nb_command - 1 && pipe(data -> fd) == -1)
			free_and_exit(PIPE_FAILED, EXIT_FAILURE, data, false);
		data -> pid[j] = fork();
		if (data -> pid[j] == -1)
			free_and_exit(FORK_FAILED, EXIT_FAILURE, data, false);
		if (data -> pid[j] == 0)
		{
			exec_command(data, argv[j + i], j);
		}
		else
		{
			close(data -> fd[1]);
			if (data -> previous_pipe != -1)
				close(data->previous_pipe);
			data -> previous_pipe = data -> fd[0];
			++j;
		}
	}
	j = 0;
	while (j < data->nb_command)
	{
		waitpid(data->pid[j], NULL, 0);
		++j;
	}
}


int		main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc < 5)
		return (1);

	init_struct(&data, argc, argv, envp);
	fork_command(&data, argv, 2 + (data.limiter != NULL));
}
