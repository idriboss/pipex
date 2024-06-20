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

static char	*check_var(char *input)
{
	char *var;

	
}

void	input_to_file(char **input_join, t_data *data)
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

char	*get_input(t_data *data)
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
		check_variable(input);
		input_join = ft_re_strjoin(input_join, input);
		if (input_join == NULL)
			input_failed("here_doc: ft_re_strjoin", input, input_join, data);
		ft_free((void **)&input);
	}
	return (input_join);
}