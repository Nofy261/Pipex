/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:12:17 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/19 08:25:28 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_infile(t_cmd *cmd, char **argv)
{
	cmd->infile = argv[1];
	cmd->fd_infile = open(argv[1], O_RDONLY);
	if (cmd->fd_infile == -1)
	{
		perror("infile failed");
		cmd->error_infile++;
		return (1);
	}
	return (0);
}

static int	open_outfile(t_cmd *cmd, char **argv)
{
	cmd->outfile = argv[4];
	cmd->fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_outfile == -1)
	{
		perror("outfile failed");
		cmd->error_outfile++;
		return (1);
	}
	return (0);
}

int	open_files(t_cmd *cmd, char **argv)
{
	int	status_code;

	status_code = open_infile(cmd, argv);
	status_code = open_outfile(cmd, argv);
	return (status_code);
}
