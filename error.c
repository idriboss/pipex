/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:57:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/14 18:37:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_err_and_exit(const char *err, int code)
{
	ft_putendl_fd((char *)err, STDERR_FILENO);
	exit(code);
}

// void	heredoc_error(int fd, char *input, t_data *data)
// {
// 	ft_close_fd(&fd);
// }

void	free_and_exit(const char *err, int code, t_data *data, bool fail)
{
	int	i;

	i = -1;
	ft_free((void **)&data->pid);
	ft_free((void **) &data->command_path);
	if (fail == true)
	{
		perror(err);
		exit(code);
	}
	print_err_and_exit(err, code);
}