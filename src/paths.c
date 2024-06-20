/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:58:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/06/20 19:10:30 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**envp_paths(t_data *data)
{
	char	**paths;
	int		i;

	i = 0;
	if (data->envp == NULL)
		return (NULL);
	while (data->envp[i] && !ft_strnstr(data->envp[i], "PATH", 4))
		i++;
	if (data->envp[i] == NULL)
		return (NULL);
	paths = ft_split(data->envp[i] + 5, ':');
	if (!paths)
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
	i = 0;
	while (paths[i] != NULL)
	{
		paths[i] = ft_re_strjoin(paths[i], "/");
		if (paths[i] == NULL)
			free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
		i++;
	}
	return (paths);
}

char	*command_path(char *command, t_data *data)
{
	char	*path;
	int		i;

	if (access(command, F_OK) == 0)
	{
		path = ft_strdup(command);
		if (path == NULL)
			free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
		return (path);
	}
	i = 0;
	while (data->env_paths != NULL && data->env_paths[i])
	{
		path = ft_strjoin(data->env_paths[i], command);
		if (path == NULL)
			free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
		if (access(path, F_OK) == 0)
			return (path);
		ft_free((void **)&path);
		i++;
	}
	path = ft_strdup(command);
	if (path == NULL)
		free_and_exit(MALLOC_FAILED, EXIT_FAILURE, data, false);
	return (path);
}
