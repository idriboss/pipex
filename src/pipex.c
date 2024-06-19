/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:50 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/17 14:04:03 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
		return (1);
	init_struct(&data, argc, argv, envp);
	fork_command(&data, argv, 2 + (data.limiter != NULL));
	free_and_exit(NULL, EXIT_SUCCESS, &data, false);
}
