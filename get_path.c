/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:16 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/04 11:49:21 by nolecler         ###   ########.fr       */
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
	perror("Error : path not found ");
	return (NULL);
}

char	*get_path_complete(char **envp, char *cmd)
{	
	int	i;
	char **path;
	char *tmp;
	char *final_path;
	
	i = 0;
	path = find_path(envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/"); // (MALLOC dans strjoin donc FREE)
		final_path = ft_strjoin(tmp, cmd); // (MALLOC);
		free(tmp);
		if (access(final_path, X_OK) == 0)
		{
			free_all(path);
			return (final_path);
		}
		// else
		// 	ft_putstr_fd("Error : Access denied\n", 2);
		free(final_path);
		i++;
	}
	// if (access(cmd, F_OK) == 0)
	// 	return (cmd);
	free_all(path);
	return (NULL);
}

// gerer si la commande donné en argument n'existe pas : renvoie 0 + message d erreur : command not found


// void	check_access(char *final_path, char **path)
// {
// 	if (access(final_path, X_OK) == 0)
// 	{
// 		free_all(path);
// 		return (final_path);
// 	}
// 	else if (access(final_path, X_OK) == -1)
// 		ft_putstr_fd("Error open: no such file or directory\n", 2);
// }

	// else if (access(final_path, R_OK) == -1)
	// 	ft_putstr_fd("Error open: permission denied\n", 2);
	// else if (access(final_path, W_OK) == -1)
	// 	ft_putstr_fd("Error open: permission denied\n", 2);
