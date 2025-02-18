/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:16 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/18 19:23:53 by nolecler         ###   ########.fr       */
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
	return (NULL);
}


static int	verif_validate_command(char **full_cmd)
{
	
	if (full_cmd == NULL || full_cmd[0] == NULL || full_cmd[0][0] == '\0')
	{
		free_all(full_cmd);
		return (1);
	}
	return (0);
}


char	**get_path_complete(t_cmd *cmd, char **path, char *command)
{
	int	i;
	
	cmd->full_cmd = ft_split(command, ' ');
	if (verif_validate_command(cmd->full_cmd) == 1)
		return (NULL);
	if (access(cmd->full_cmd[0], X_OK) == 0)
		return (cmd->full_cmd);
	i = 0;
	while (path[i])
	{
		cmd->tmp = ft_strjoin(path[i], "/");
		cmd->is_valid_cmd = ft_strjoin(cmd->tmp, cmd->full_cmd[0]);
		free(cmd->tmp);
		if (access(cmd->is_valid_cmd, X_OK) == 0)
		{
			free(cmd->full_cmd[0]);
			cmd->full_cmd[0] = cmd->is_valid_cmd;
			return (cmd->full_cmd);
		}
		free(cmd->is_valid_cmd);
		i++;
	}
	free_all(cmd->full_cmd); // retourne le tab de tab ("grep toi") = commande entiere
	return (NULL);
}


// tab de tab **full_cmd = {[0 = grep], [1 = toi], NULL};
// full_cmd[0] = grep; full_cmd[1] = toi;
// is_valid_cmd = /usr/bin/cat 
// is_valid_cmd = full_cmd[0] = /usr/bin/grep;
