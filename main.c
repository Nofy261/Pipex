/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 15:52:17 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	init_struct(&cmd);
	if (!check_envp(envp))
		return (1);
	if (argc == 5)
	{
		open_files(&cmd, argv);
		cmd.paths = get_valid_paths(envp);
		if (cmd.paths == NULL)
		{
			close_fds(&cmd);
			exit(1);
		}
		if (validate_commands(&cmd, argv) == 0 || initialize_pipe(&cmd) == 0)
		{
			close_and_free(&cmd);
			return (1);
		}
		process_start(&cmd, envp);
		close_and_free(&cmd);
	}
	else
		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}
