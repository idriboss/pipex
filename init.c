/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:47 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/15 02:05:28 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_limiter(char *input, t_data *data)
{
	size_t	input_len;

	input_len = ft_strlen(input);
	if (input_len <= 1)
	{
		return (0);
	}
	if (input[input_len - 1] == '\n')
	{
		input[input_len - 1] = '\0';
	}
	if (ft_strcmp(input, data->limiter) == 0)
	{
		return (1);
	}
	else
	{
		input[input_len - 1] = '\n';
		return (0);
	}
}

char	*heredoc_file(t_data *data)
{
	int	fd;
	char	*input;
	
	fd = open(HERE_DOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		free_and_exit("here_doc", EXIT_FAILURE, data, true);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		input = get_next_line(STDIN_FILENO);
		if (is_limiter(input, data) == 1)
		{
			ft_free((void **)&input);
			return (HERE_DOC_FILE);
		}
		if (ft_putstr_fd(input, fd) == -1)
		{
			heredoc_error(fd, input, data);
		}
		ft_free((void **)&input);
	}
	close (fd);
	return (HERE_DOC_FILE);
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
		data->input_file = heredoc_file(data);
	}
	else
	{
		if (argc < 5)
			print_err_and_exit(USAGE, EXIT_FAILURE, false);
		data->input_file = argv[1];
		data->nb_command = argc - 3;
	}
	data->envp = envp;
	data->output_file = argv[argc - 1];
	data->previous_pipe = -1;
	data->pid = malloc(sizeof(int) * (data->nb_command));
	if (data->pid == NULL)
		print_err_and_exit(MALLOC_FAILED, EXIT_FAILURE, false);
}