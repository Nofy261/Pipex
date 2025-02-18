/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:13:48 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/18 19:38:28 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	**get_valid_paths(t_cmd *cmd, char **envp)
{
	char	**paths;

	paths = find_path(envp);
	if (paths == NULL || paths[0] == NULL || paths[0][0] == '\0')
	{
		ft_putstr_fd("Error : path not found\n", 2);
		free_all(paths);
		close_fds(cmd);
		return (NULL);
	}
	return (paths);
}

void	validate_command(t_cmd *cmd, char **argv, int *exit_code)
{
	cmd->good_paths1 = get_path_complete(cmd, cmd->paths, argv[2]);
	if (!cmd->good_paths1)
	{
		if (cmd->error_infile == 0)
		{
			ft_putstr_fd("Error: Command 1 not found\n", 2);
			*exit_code = 127;
		}
	}
	cmd->good_paths2 = get_path_complete(cmd, cmd->paths, argv[3]);
	if (!cmd->good_paths2)
	{	
		if (cmd->error_outfile == 0)
		{
			ft_putstr_fd("Error: Command 2 not found\n", 2);
			*exit_code = 127;
		}
	}
	else if (cmd->error_outfile == 0)
		*exit_code = 0;
}



// int validate_command_2(t_cmd *cmd, char **argv) // A VERIFIER SI  A ENLEVER OU PAS???
// {
// 	cmd->good_paths2 = get_path_complete(cmd, cmd->paths, argv[3]);
// 	if (!cmd->good_paths2)
// 	{	
// 		ft_putstr_fd("Error: Command 2 not found\n", 2);
// 		return (127);
// 	}
// 	return (0);
// }



void	initialize_pipe(t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
	{
		ft_putstr_fd("pipe failed\n", 2);
		close_and_free(cmd);
		exit(EXIT_FAILURE);
	}
}


