/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/13 19:03:39 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h> //// 

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	init_struct(&cmd);
	if (check_envp(envp) == 0)
		return (1);
	if (argc == 5)
	{
		open_files(&cmd, argv);
		cmd.paths = get_valid_paths(envp);
		if (cmd.paths == NULL)
		{
			close_fds(&cmd);
			exit(1); // a revoir 
		}
		validate_command_1(&cmd, argv);
		validate_command_2(&cmd, argv);// exit , return(1)?
		initialize_pipe(&cmd);
		process_start(&cmd, envp);
		close_and_free(&cmd);
	}
	else
		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}


// Avant de lancer process_start , recuperer les info de open_files et validate_command 
// afin de savoir si on lance ou pas le programme
 


// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd	cmd;

// 	init_struct(&cmd);
// 	if (!check_envp(envp))
// 		return (1);
// 	if (argc == 5)
// 	{
// 		open_files(&cmd, argv);
// 		cmd.paths = get_valid_paths(envp); // seg fault test sans path
// 		if (cmd.paths == NULL)
// 		{
// 			close_fds(&cmd);
// 			exit(1); // a revoir 
// 		}
// 		// si la commande n est pas valide on ne doit pas exit
// 		if (validate_commands(&cmd, argv) == 0 || initialize_pipe(&cmd) == 0)
// 		{
// 			close_and_free(&cmd);
// 			return (1);
// 		}
// 		process_start(&cmd, envp);
// 		close_and_free(&cmd);
// 	}
// 	else
// 		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);
// 	return (0);
// }
