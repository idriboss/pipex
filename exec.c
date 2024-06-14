#include "pipex.h"

static void	exec_command(t_data *data, char *cmd, int j)
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
	{
		waitpid(data->pid[j], NULL, 0);
		++j;
	}
}
