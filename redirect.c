/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/14 16:58:55 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect(t_data *data, int j)
{
	int	infile_fd;
	int	outfile_fd;
	
	// printf("variables before redirect:\n");
	if (j == 0)
	{
		// fprintf(stderr, "First\n");
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
		// fprintf(stderr, "Last\n");
		outfile_fd = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			close(outfile_fd);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(outfile_fd);
		// fprintf(stderr, "Last ok\n");
	}
	else
	{
		// fprintf(stderr, "Middle\n");
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			close (data->fd[1]);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(data->fd[0]);
	}
	if (data->previous_pipe != -1)
	{
		// fprintf(stderr, "previous_pipe: [%d]\n", data->previous_pipe);
		if (dup2(data->previous_pipe, STDIN_FILENO) == -1)
		{
			close(data->previous_pipe);
			free_and_exit(NULL, EXIT_FAILURE, data, true);
		}
		close(data->previous_pipe);
	}
}