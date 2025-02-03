/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:12:17 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/03 14:12:59 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char **argv)
{
	int	fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror("Error opening infile ");
		return(-1);
	}
	return(fd_infile);
}
int	open_outfile(char **argv)
{
	int fd_outfile;
	
	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_outfile == -1)
	{
		perror("Error opening outfile ");
		return (-1);
	}
	return (fd_outfile);
}