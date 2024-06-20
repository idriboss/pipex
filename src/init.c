/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:47 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/20 19:34:51 by ibaby            ###   ########.fr       */
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

static void	input_to_file(char **input_join, t_data *data)
{
	int	fd;

	fd = open(HERE_DOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_free((void **)input_join);
		free_and_exit("here_doc", EXIT_FAILURE, data, true);
	}
	if (ft_putstr_fd(*input_join, fd) == -1)
	{
		ft_close_fd(&fd);
		fd = -1;
		ft_free((void **)input_join);
		free_and_exit("here_doc: ", EXIT_FAILURE, data, false);
	}
	ft_close_fd(&fd);
	fd = -1;
	ft_free((void **)input_join);
	*input_join = NULL;
}

static char	*get_input(t_data *data)
{
	char	*input;
	char	*input_join;

	input_join = ft_strdup("");
	if (input_join == NULL)
		free_and_exit("here_doc: ft_strdup failed", 1, data, false);
	while (1)
	{
		if (write(1, "pipe heredoc> ", 14) == -1)
			input_failed("here_doc: write", input, input_join, data);
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			input_failed("here_doc: get_next_line", input, input_join, data);
		if (is_limiter(input, data) == 1)
		{
			ft_free((void **)&input);
			break ;
		}
		input_join = ft_re_strjoin(input_join, input);
		if (input_join == NULL)
			input_failed("here_doc: ft_re_strjoin", input, input_join, data);
		ft_free((void **)&input);
	}
	return (input_join);
}

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
			print_err_and_exit(USAGE_BONUS, EXIT_FAILURE, false, data);
		data->limiter = argv[2];
		data->nb_command = argc - 4;
		get_heredoc_file(data);
		data->input_file = HERE_DOC_FILE;
	}
	else
	{
		if (argc < 5)
			print_err_and_exit(USAGE, EXIT_FAILURE, false, data);
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
