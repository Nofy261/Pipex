/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:13:48 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/13 19:06:12 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_valid_paths(char **envp)
{
	char	**paths;

	paths = find_path(envp);
	if (!paths)  // a verifier les leaks 
		return(NULL);
	if (paths == NULL || paths[0] == NULL || paths[0][0] == '\0')
	{
		ft_putstr_fd("Error\nInvalid path", 2);
		free_all(paths);
		return (NULL);
	}
	return (paths);
}


void  validate_command_1(t_cmd *cmd, char **argv)
{
	cmd->good_paths1 = get_path_complete(cmd, cmd->paths, argv[2]);
	if (!cmd->good_paths1)
		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);

}

void validate_command_2(t_cmd *cmd, char **argv)
{
	cmd->good_paths2 = get_path_complete(cmd, cmd->paths, argv[3]);
	if (!cmd->good_paths2)
		ft_putstr_fd("Error: Command 2 not found\n", 2);
}


void	initialize_pipe(t_cmd *cmd)
{
	if (pipe(cmd->fd) == -1)
	{
		ft_putstr_fd("pipe failed\n", 2);
		close_and_free(cmd);
		exit(EXIT_FAILURE);
	}
}


// int	validate_commands(t_cmd *cmd, char **argv)
// {
// 	// good_paths1 = {[usr/bin/cat], NULL}; (cmd1 = cat)
// 	cmd->good_paths1 = get_path_complete(cmd, cmd->paths, argv[2]);
// 	if (!cmd->good_paths1)
// 	{
// 		ft_putstr_fd("Error: Command 1 not found\n", 2);
// 		return (0); // base
// 	}
// 	// good_paths2 = {[/usr/bin/grep], [toi], NULL};
// 	// good_path2[0] = "/usr/bin/grep";
// 	// good_path2[1] = "toi";
// 	cmd->good_paths2 = get_path_complete(cmd, cmd->paths, argv[3]);
// 	if (!cmd->good_paths2)
// 	{
// 		ft_putstr_fd("Error: Command 2 not found\n", 2);
// 		return (0);
// 	}
// 	return (1);
// }


// int	initialize_pipe(t_cmd *cmd)
// {
// 	if (pipe(cmd->fd) == -1)
// 	{
// 		ft_putstr_fd("pipe failed\n", 2);
// 		return (0);
// 	}
// 	return (1);
// }
