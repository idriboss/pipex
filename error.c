/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:57:54 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/12 23:21:09 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	ft_free(void **elem)
{
	if (*elem == NULL)
		return ;
	free(*elem);
	*elem = NULL;
}
void	print_err_and_exit(const char *err, int code)
{
	ft_putendl_fd((char *)err, STDERR_FILENO);
	exit(code);
}

void	free_and_exit(const char *err, int code, t_data *data, bool fail)
{
	ft_free((void **)&data -> pid);
	print_err_and_exit(err, code);	
}