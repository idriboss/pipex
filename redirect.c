/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/15 19:56:55 by ibaby            ###   ########.fr       */
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
		ft_close_fd(&data->fd[0]);
		infile_fd = open(data->input_file, O_RDONLY, 0644);
		if (infile_fd == -1)
			free_and_exit(data->input_file, EXIT_FAILURE, data, true);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			ft_close_fd(&infile_fd);
			free_and_exit(data->input_file, EXIT_FAILURE, data, true);
		}
		ft_close_fd(&infile_fd);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			ft_close_fd(&data->fd[1]);
			free_and_exit("dup2(fd[1])", EXIT_FAILURE, data, true);
		}
		ft_close_fd(&data->fd[1]);
	}
	else if (j == data->nb_command - 1)
	{
		// fprintf(stderr, "Last\n");
		outfile_fd = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			free_and_exit(data->output_file, 1, data, true);
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			ft_close_fd(&outfile_fd);
			free_and_exit(data->output_file, EXIT_FAILURE, data, true);
		}
		ft_close_fd(&outfile_fd);
	}
	else
	{
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			ft_close_fd(&data->fd[1]);
			free_and_exit("dup2(fd[1])", EXIT_FAILURE, data, true);
		}
		ft_close_fd(&data->fd[0]);
	}
	if (data->previous_pipe != -1)
	{
		// fprintf(stderr, "previous_pipe: [%d]\n", data->previous_pipe);
		if (dup2(data->previous_pipe, STDIN_FILENO) == -1)
		{
			ft_close_fd(&data->previous_pipe);
			free_and_exit("dup2(previous_pipe)", EXIT_FAILURE, data, true);
		}
		ft_close_fd(&data->previous_pipe);
	}
}