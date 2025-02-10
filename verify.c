/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:13:48 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 15:53:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_valid_paths(char **envp)
{
	char	**paths;

	paths = find_path(envp);
	if (paths == NULL || paths[0] == NULL || paths[0][0] == '\0')
	{
		ft_putstr_fd("Error\nInvalid path", 2);
		free_all(paths);
		return (NULL);
	}
	return (paths);
}

int	error_command_null(t_cmd *cmd, char **command_path, char *error_message)
{
	if (command_path == NULL)
	{
		ft_putstr_fd(error_message, 2);
		free_all_paths(cmd);
		return (1);
	}
	return (0);
}


int	validate_commands(t_cmd *cmd, char **argv)
{
	cmd->good_paths1 = get_path_complete(cmd, cmd->paths, argv[2]);
	if (!cmd->good_paths1)
	{
		ft_putstr_fd("Error: Command 1 not found in PATH\n", 2);
		return (0);
	}
	cmd->good_paths2 = get_path_complete(cmd, cmd->paths, argv[3]);
	if (!cmd->good_paths2)
	{
		ft_putstr_fd("Error: Command 2 not found in PATH\n", 2);
		return (0);
	}
	return (1);
}

int	initialize_pipe(t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
	{
		ft_putstr_fd("pipe failed\n", 2);
		return (0);
	}
	return (1);
}