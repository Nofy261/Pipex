/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:07:22 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/11 11:57:06 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_cmd *cmd)
{
	cmd->pid1 = -1;
	cmd->pid2 = -1;
	cmd->fd[0] = -1;
	cmd->fd[1] = -1;
	cmd->fd_infile = -1;
	cmd->fd_outfile = -1;
	cmd->error_infile = 0;
	cmd->error_outfile = 0;
	cmd->good_paths1 = NULL;
	cmd->good_paths2 = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->paths = NULL;
	cmd->tmp = NULL;
	cmd->full_cmd = NULL;
	cmd->is_valid_cmd = NULL;
}
