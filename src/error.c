/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:57:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/17 14:07:05 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_failed(char *err, char *input, char *input_join, t_data *data)
{
	ft_free((void **)&input);
	ft_free((void **)&input_join);
	free_and_exit(err, EXIT_FAILURE, data, false);
}

void	print_err_and_exit(const char *err, int code, bool errno)
{
	if (errno == true)
	{
		perror(err);
		exit(code);
	}
	if (err != NULL)
	{
		ft_putendl_fd((char *)err, STDERR_FILENO);
	}
	exit(code);
}

void	free_and_exit(const char *err, int code, t_data *data, bool errno)
{
	if (data->limiter != NULL)
	{
		unlink(data->input_file);
		data->limiter = NULL;
	}
	ft_free((void **)&data->pid);
	ft_free((void **) &data->command_path);
	free_2d_array((void ***) &data->command);
	free_2d_array((void ***)&data->env_paths);
	ft_close_fd(&data->fd_to_close);
	ft_close_fd(&data->fd[0]);
	ft_close_fd(&data->fd[1]);
	if (code == 2)
	{
		print_err_and_exit("command not found", code, true);
	}
	else
	{
		print_err_and_exit(err, code, errno);
	}
}
