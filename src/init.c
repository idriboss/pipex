/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:47 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/20 17:13:14 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



static void	get_heredoc_file(t_data *data)
{
	char	*input;

	input = get_input(data);
	input_to_file(&input, data);
}

void	init_struct(t_data *data, int argc, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			print_err_and_exit(USAGE_BONUS, EXIT_FAILURE, false);
		data->limiter = argv[2];
		data->nb_command = argc - 4;
		get_heredoc_file(data);
		data->input_file = HERE_DOC_FILE;
	}
	else
	{
		if (argc < 5)
			print_err_and_exit(USAGE, EXIT_FAILURE, false);
		data->input_file = argv[1];
		data->nb_command = argc - 3;
	}
	data->previous_pipe = -1;
	data->envp = envp;
	data->env_paths = envp_paths(data);
	data->output_file = argv[argc - 1];
	data->pid = malloc(sizeof(int) * (data->nb_command));
	if (data->pid == NULL)
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
}
