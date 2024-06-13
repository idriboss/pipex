#include "pipex.h"

char	**possible_cmd_paths(char *command, t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	while (data->envp[i] && !ft_strnstr(data->envp[i], "PATH", 4))
        i++;
	if (!data->envp[i] || data->envp[i][0] != 'P' || data->envp[i][3] != 'H')
    	free_and_exit("env: paths missing", EXIT_FAILURE, data, false);
	paths = ft_split(data->envp[i] + 5, ':');
	if (!paths)
		free_and_exit("split function failed", EXIT_FAILURE, data, false);
	i = 0;
	while(paths[i])
	{
		paths[i] = multi_re_strjoin(3, paths[i], "/", command);
		if (!paths[i++])
			free_and_exit("multi_re_strjoin function failed", EXIT_FAILURE, data, false);
	}
	return (paths);
}

char	*command_path(char *command, t_data *data)
{
	int		i;
	char	**path;
	char	*str;

	i = 0;
	path = possible_cmd_paths(command, data);
	while (path[i])
	{
		if (access(path[i], F_OK) == 0)
			break;
		i++;
	}
	if (path[i] == NULL)
	{
		free_2d_array((void ***)&path);
		return (NULL);
	}
	str = ft_strdup(path[i]);
	if (str == NULL)
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
	free_2d_array((void ***)&path);
	return (str);
}

void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			print_err_and_exit(USAGE_BONUS, EXIT_FAILURE);
		data->limiter = argv[2];
		data->nb_command = argc - 4;
	}
	else
	{
		if (argc < 5)
			print_err_and_exit(USAGE, EXIT_FAILURE);
		data->input_file = argv[1];
		data->nb_command = argc - 3;

	}
	data->envp = envp;
	data->output_file = argv[argc - 1];
	data->previous_pipe = -1;
	data->pid = malloc(sizeof(int) * (data->nb_command));
	if (data->pid == NULL)
		print_err_and_exit(MALLOC_FAILED, EXIT_FAILURE);
}

void	redirect(t_data *data, int j)
{
	int	infile_fd;
	int	outfile_fd;
	if (j == 0)
	{
		close(data->fd[0]);
		infile_fd = open(data->input_file, O_RDONLY, 0644);
		if (infile_fd == -1)
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			close(infile_fd);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(infile_fd);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			close(data->fd[1]);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(data->fd[1]);
	}
	else if (j == data->nb_command - 1)
	{
		outfile_fd = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			close(outfile_fd);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(outfile_fd);
	}
	else
	{
		close(data->fd[0]);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			close (data->fd[1]);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close (data->fd[0]);
	}
	if (data->previous_pipe != -1)
	{
		if (dup2(data->previous_pipe, STDIN_FILENO) == -1)
		{
			close(data->previous_pipe);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(data->previous_pipe);
	}
}

void	exec_command(t_data *data, char *cmd, int j)
{
	char	**command;
	char	*cmd_path;

	command = ft_split(cmd, ' ');
	if (command == NULL)
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
	cmd_path = command_path(command[0], data);
	redirect(data, j);
	execve(cmd_path, command, data->envp);
	free_and_exit(NULL, EXIT_FAILURE, data, true);
}


void	fork_command(t_data *data, char **argv, int i)
{
	int	j;

	j = 0;
	while (j < data->nb_command)
	{
		if (j != data->nb_command - 1 && pipe(data->fd) == -1)
			free_and_exit(PIPE_FAILED, EXIT_FAILURE, data, false);
		data->pid[j] = fork();
		if (data->pid[j] == -1)
			free_and_exit(FORK_FAILED, EXIT_FAILURE, data, false);
		if (data->pid[j] == 0)
		{
			exec_command(data, argv[j + i], j);
		}
		else
		{
			wait(NULL);
			close(data->fd[1]);
			if (data->previous_pipe != -1)
				close(data->previous_pipe);
			data->previous_pipe = data->fd[0];
			++j;
		}
	}
	j = 0;
	while (j < data->nb_command)
		waitpid(data->pid[j++], NULL, 0);
}


int		main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc < 5)
		return (1);
	init_struct(&data, argc, argv, envp);
	fork_command(&data, argv, 2 + (data.limiter != NULL));

	free_and_exit("FINISH", EXIT_SUCCESS, &data, false);
}
