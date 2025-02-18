/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:08:02 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/18 19:43:35 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execute_child2(t_cmd *cmd, char **envp)
{
	dup2(cmd->fd[0], STDIN_FILENO);
   	dup2(cmd->fd_outfile, STDOUT_FILENO);
   	close_fds(cmd);
   	if (cmd->good_paths2 && cmd->good_paths2[0] && !cmd->error_outfile)
	{
	// good_paths2 = {[/usr/bin/grep], [toi], NULL};
	// good_path2[0] = "/usr/bin/grep";
	// execve( /usr/bin/grep, grep toi, envp);
		
		execve(cmd->good_paths2[0], cmd->good_paths2, envp);
    	ft_putstr_fd("Error: Failed to execute command2\n", 2);
	}
    free_all_paths(cmd);
    exit(EXIT_FAILURE);
}


static int	execute_child1(t_cmd *cmd, char **envp)
{
	dup2(cmd->fd_infile, STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	close_fds(cmd);
	if (cmd->good_paths1 && cmd->good_paths1[0] && !cmd->error_infile)
	{
		execve(cmd->good_paths1[0], cmd->good_paths1, envp);
		ft_putstr_fd("Error: Failed to execute command1\n", 2);
	}
	free_all_paths(cmd);
	exit(EXIT_FAILURE);
}


void	process_start(t_cmd *cmd, char **envp)
{
	
	cmd->pid1 = fork();
	if (cmd->pid1 == -1)
	{
		ft_putstr_fd("fork failed 1\n", 2);
		close_and_free(cmd);
		exit(1);// a modif ?
	}
	if (cmd->pid1 == 0 && !cmd->error_infile)
		execute_child1(cmd, envp);
	cmd->pid2 = fork();
	if (cmd->pid2 == -1)
	{
		ft_putstr_fd("fork failed 2\n", 2);
		close_and_free(cmd);
		exit(1); // a modif ?
	}
	if (cmd->pid2 == 0 && !cmd->error_outfile)
		execute_child2(cmd, envp);
	close_and_free(cmd);
	waitpid(cmd->pid1, NULL, 0);
	waitpid(cmd->pid2, NULL, 0);
}
