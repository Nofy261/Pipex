/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:12:17 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 08:09:24 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_cmd *cmd, char **argv)
{
	cmd->infile = argv[1];
	cmd->fd_infile = open(argv[1], O_RDONLY);
	if (cmd->fd_infile == -1)
	{
		ft_putstr_fd("Error opening infile\n ", 2);
		exit(1);
	}
}

void	open_outfile(t_cmd *cmd, char **argv)
{
	cmd->outfile = argv[4];
	cmd->fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_outfile == -1)
	{
		ft_putstr_fd("Error opening outfile\n ", 2);
		exit(1);
	}
}

void	open_files(t_cmd *cmd, char **argv)
{
	open_infile(cmd, argv);
	open_outfile(cmd, argv);
}