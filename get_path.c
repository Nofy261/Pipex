/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:16 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/08 19:00:54 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
		i++;
	}
	ft_putstr_fd("Error : path not found\n", 2);
	return (NULL);
}

char	*get_path_complete(char **envp, char *cmd)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*final_path;

	i = 0;
	// cas ou l'on donne directement le chemin en cmd
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = find_path(envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(tmp, cmd);
		tmp = free_and_null(tmp);
		if (access(final_path, X_OK) == 0)
		{
			free_all(path);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_all(path);
	return (NULL);
}
