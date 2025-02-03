/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:16 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/03 14:16:41 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **envp)
{
	int	i;
	char **path;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{	
			path = ft_split(envp[i] + 5, ':'); // (MALLOC)
			return (path);
		}
		i++;
	}
	// exit + message d'erreur;
	return (NULL);
}

char	*get_path_complete(char **envp, char *cmd)
{	
	//int j;
	int	i;
	char **path;
	char *tmp;
	char *final_path;
	
	//j = 0;
	i = 0;
	
	path = find_path(envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/"); // (MALLOC dans strjoin donc FREE)
		final_path = ft_strjoin(tmp, cmd); // (MALLOC);
		free(tmp);
		if (access(final_path, X_OK ) == 0)
		{
			// while(path[j])
			// {
			// 	free(path[j]);
			// 	j++;
			// }
			// free(path);
			return (final_path);
		}	
		free(final_path);
		i++;
	}
	free_all(path);
	return (NULL);
}
