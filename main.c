/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/18 19:42:39 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	int		exit_code;
	
	exit_code = 0;
	init_struct(&cmd);
	if (check_envp(envp) == 0)
		return (1);
	if (argc == 5)
	{
		exit_code = open_files(&cmd, argv);
		cmd.paths = get_valid_paths(&cmd, envp);
		if (cmd.paths == NULL)
			return (1);
		validate_command(&cmd, argv, &exit_code);
		initialize_pipe(&cmd);
		process_start(&cmd, envp);
		close_and_free(&cmd);
	}
	else
	{
		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit_code = 1;
	}
	return (exit_code);
}




