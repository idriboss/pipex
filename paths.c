/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/15 16:36:46 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**possible_cmd_paths(char *command, t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	while (data->envp[i] && !ft_strnstr(data->envp[i], "PATH", 4))
        i++;
	if (!data->envp[i] || data->envp[i][0] != 'P' || data->envp[i][3] != 'H')
    	free_and_exit("env: paths missing", EXIT_FAILURE, data, false);
	paths = ft_split(data->envp[i] + 5, ':');
	if (!paths)
		free_and_exit("split function failed", EXIT_FAILURE, data, false);
	i = 0;
	while(paths[i])
	{
		paths[i] = multi_re_strjoin(3, paths[i], "/", command);
		if (!paths[i++])
		{
			free_2d_array((void ***)&paths);
			free_and_exit("multi_re_strjoin function failed", EXIT_FAILURE, data, false);
		}
	}
	return (paths);
}

char	*command_path(char *command, t_data *data)
{
	int		i;
	char	**path;
	char	*str;

	i = 0;
	if (access(command, F_OK) == 0)
	{
		str = ft_strdup(command);
		if (str == NULL)
			free_and_exit("strdup function failed", EXIT_FAILURE,data, false);
		return (str);
	}
	path = possible_cmd_paths(command, data);
	while (path[i])
	{
		if (access(path[i], F_OK) == 0)
			break;
		i++;
	}
	if (path[i] == NULL)
	{
		free_2d_array((void ***)&path);
		return (NULL);
	}
	str = ft_strdup(path[i]);
	if (str == NULL)
	{
		free_2d_array((void ***)&path);
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
	}
	free_2d_array((void ***)&path);
	return (str);
}
