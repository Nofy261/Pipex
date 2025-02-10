/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 08:19:54 by nolecler         ###   ########.fr       */
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
			exit(1);
		if (validate_commands(&cmd, argv) == 0 || initialize_pipe(&cmd) == 0)
		{
			close_fds(&cmd);
			free_all_paths(&cmd);
			return (1);
		}
		child_first(&cmd, envp);
		close_fds(&cmd);
		free_all_paths(&cmd);
	}
	else
		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}
