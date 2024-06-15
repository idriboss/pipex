/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:45 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/15 18:21:05 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

static void	exec_command(t_data *data, char *cmd, int j)
{
	data->command = ft_split(cmd, ' ');
	if (data->command == NULL)
		free_and_exit("ft_split function failed", EXIT_FAILURE, data, false);
	data->command_path = command_path(data->command[0], data);
	if (data->command_path == NULL)
		free_and_exit("command not found", EXIT_FAILURE, data, true);
	redirect(data, j);
	execve(data->command_path, data->command, data->envp);
	free_and_exit("execve", EXIT_FAILURE, data, true);
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
			close_fd(&data->fd[1]);
			if (data->previous_pipe != -1)
				close_fd(&data->previous_pipe);
			data->previous_pipe = data->fd[0];
			++j;
		}
	}
}
