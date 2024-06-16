/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/16 15:19:53 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// void	outfile_to_stdout(t_data *data, )
// {}

void	redirect(t_data *data, int j)
{
	int	infile;
	int	outfile;

	if (j == 0)
	{
		ft_close_fd(&data->fd[0]);
		infile = open(data->input_file, O_RDONLY, 0644);
		if (infile == -1)
			free_and_exit(data->input_file, EXIT_FAILURE, data, true);
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			ft_close_fd(&infile);
			free_and_exit(data->input_file, EXIT_FAILURE, data, true);
		}
		ft_close_fd(&infile);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		{
			ft_close_fd(&data->fd[1]);
			free_and_exit("dup2(fd[1])", EXIT_FAILURE, data, true);
		}
		ft_close_fd(&data->fd[1]);
	}
	else if (j == data->nb_command - 1)
	{
		outfile = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			free_and_exit(data->output_file, 1, data, true);
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			ft_close_fd(&outfile);
			free_and_exit(data->output_file, EXIT_FAILURE, data, true);
		}
		ft_close_fd(&outfile);
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
		if (dup2(data->previous_pipe, STDIN_FILENO) == -1)
		{
			ft_close_fd(&data->previous_pipe);
			free_and_exit("dup2(previous_pipe)", EXIT_FAILURE, data, true);
		}
		ft_close_fd(&data->previous_pipe);
	}
}