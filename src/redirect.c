/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/20 18:36:57 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(int *fd, int fd_to_replace, t_data *data, char *fd_name)
{
	if (dup2(*fd, fd_to_replace) == -1)
	{
		ft_close_fd(fd);
		free_and_exit(fd_name, EXIT_FAILURE, data, true);
	}
	ft_close_fd(fd);
}

void	file_to_stdin(char *file_to_stdin, t_data *data)
{
	int	fd;

	ft_close_fd(&data->fd[0]);
	fd = open(file_to_stdin, O_RDONLY, 0644);
	if (fd == -1)
		free_and_exit(file_to_stdin, EXIT_FAILURE, data, true);
	ft_dup2(&fd, STDIN_FILENO, data, file_to_stdin);
}

void	file_to_stdout(char *file_to_stdout, t_data *data)
{
	int	fd;

	ft_close_fd(&data->fd[0]);
	ft_close_fd(&data->fd[1]);
	if (data->limiter == NULL)
	{
		fd = open(file_to_stdout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			free_and_exit(file_to_stdout, EXIT_FAILURE, data, true);
	}
	else
	{
		fd = open(file_to_stdout, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			free_and_exit(file_to_stdout, EXIT_FAILURE, data, true);
	}
	ft_dup2(&fd, STDOUT_FILENO, data, file_to_stdout);
}

void	redirect(t_data *data, int j)
{
	if (j == 0)
	{
		file_to_stdin(data->input_file, data);
		ft_dup2(&data->fd[1], STDOUT_FILENO, data, "pipe[1]");
	}
	else if (j == data->nb_command - 1)
	{
		file_to_stdout(data->output_file, data);
	}
	else
	{
		ft_close_fd(&data->fd[0]);
		ft_dup2(&data->fd[1], STDOUT_FILENO, data, "pipe[1]");
	}
	if (data->previous_pipe != -1)
	{
		ft_dup2(&data->previous_pipe, STDIN_FILENO, data, "previous pipe");
	}
}
