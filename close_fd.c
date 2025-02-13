/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:02:23 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 15:59:16 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_cmd *cmd)
{
	if (cmd->fd[0] >= 0)
	{
		close(cmd->fd[0]);
		cmd->fd[0] = -1;
	}
	if (cmd->fd[1] >= 0)
	{
		close(cmd->fd[1]);
		cmd->fd[1] = -1;
	}
	if (cmd->fd_infile >= 0)
	{
		close(cmd->fd_infile);
		cmd->fd_infile = -1;
	}
	if (cmd->fd_outfile >= 0)
	{
		close(cmd->fd_outfile);
		cmd->fd_outfile = -1;
	}
}

void	close_and_free(t_cmd *cmd)
{
	close_fds(cmd);
	free_all_paths(cmd);
}
