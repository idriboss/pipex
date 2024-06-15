/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:57:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/15 01:47:05 by ibaby            ###   ########.fr       */
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

void	print_err_and_exit(const char *err, int code, bool fail)
{
	if (fail == true)
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

void	heredoc_error(int fd, char *input, t_data *data)
{
	close_fd(&fd);
	ft_free((void **)&input);
	free_and_exit("here_doc error", EXIT_FAILURE, data, false);
}

void	free_and_exit(const char *err, int code, t_data *data, bool fail)
{
	if (data->limiter != NULL)
	{
		unlink(data->input_file);
	}
	ft_free((void **)&data->pid);
	ft_free((void **) &data->command_path);
	print_err_and_exit(err, code, fail);
}