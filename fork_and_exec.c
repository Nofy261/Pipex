/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:08:02 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 08:03:35 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_second(t_cmd *cmd, char **envp)
{
	close(cmd->fd[1]);
	dup2(cmd->fd[0], STDIN_FILENO);
	close(cmd->fd[0]);
	dup2(cmd->fd_outfile, STDOUT_FILENO);
	close (cmd->fd_outfile);
	if (cmd->good_paths2 && cmd->good_paths2[0])
		execve(cmd->good_paths2[0], cmd->good_paths2, envp);
	ft_putstr_fd("Error: Failed to execute command\n", 2);
	exit(1);
}

static void	execute_child2(t_cmd *cmd, char **envp)
{
	cmd->pid2 = fork();
	if (cmd->pid2 == -1)
	{
		ft_putstr_fd("fork failed 2\n", 2);
		close_fds(cmd);
		free_all_paths(cmd);
		exit(1);
	}
	if (cmd->pid2 == 0)
		child_second(cmd, envp);
	else
	{
		close(cmd->fd_infile);
		close(cmd->fd_outfile);
		close (cmd->fd[1]);
		close (cmd->fd[0]);
		while (waitpid(-1, NULL, 0) != -1)
			continue ;
	}
}

static int	execute_child1(t_cmd *cmd, char **envp)
{
	close_fd_child_first(cmd);
	dup2(cmd->fd_infile, STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->good_paths1 && cmd->good_paths1[0])
		execve(cmd->good_paths1[0], cmd->good_paths1, envp);
	ft_putstr_fd("Error: Failed to execute command\n", 2);
	close_fds(cmd);
	free_all_paths(cmd);
	exit(1);
}

void	child_first(t_cmd *cmd, char **envp)
{
	cmd->pid1 = fork();
	if (cmd->pid1 == -1)
	{
		ft_putstr_fd("fork failed 1\n", 2);
		close_fds(cmd);
		free_all_paths(cmd);
		exit(1);
	}
	if (cmd->pid1 == 0)
		execute_child1(cmd, envp);
	else
		execute_child2(cmd, envp);
}
