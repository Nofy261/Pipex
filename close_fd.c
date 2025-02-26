/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:02:23 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/19 08:23:31 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_cmd *cmd)
{
	if (cmd->fd[0] > 2)
	{
		close(cmd->fd[0]);
		cmd->fd[0] = -1;
	}
	if (cmd->fd[1] > 2)
	{
		close(cmd->fd[1]);
		cmd->fd[1] = -1;
	}
	if (cmd->fd_infile > 2)
	{
		close(cmd->fd_infile);
		cmd->fd_infile = -1;
	}
	if (cmd->fd_outfile > 2)
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
