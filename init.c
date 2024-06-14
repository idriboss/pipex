/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:47 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/14 18:37:35 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// int	heredoc_fd(t_data *data)
// {
// 	int	fd;
// 	char	*input;
	
// 	fd = open("heredoc_input.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	while (1)
// 	{
// 		input = get_next_line(STDIN_FILENO);
// 		if (!input)
// 		{
// 			ft_close_fd(&fd)
// 			unlink("heredoc_input.txt");
// 			free_and_exit("heredoc failed", EXIT_FAILURE, data, false);
// 		}
		
// 	}
// }

void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			print_err_and_exit(USAGE_BONUS, EXIT_FAILURE);
		data->limiter = argv[2];
		data->nb_command = argc - 4;
		//data->input_file = heredoc_fd(data);
	}
	else
	{
		if (argc < 5)
			print_err_and_exit(USAGE, EXIT_FAILURE);
		data->input_file = argv[1];
		data->nb_command = argc - 3;
	}
	data->envp = envp;
	data->output_file = argv[argc - 1];
	data->previous_pipe = -1;
	data->pid = malloc(sizeof(int) * (data->nb_command));
	if (data->pid == NULL)
		print_err_and_exit(MALLOC_FAILED, EXIT_FAILURE);
}