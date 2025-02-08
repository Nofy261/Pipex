/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:12:17 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/08 18:56:45 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char **argv)
{
	int	fd_infile;
	printf("Je suis dans open_file\n");
	fd_infile = open(argv[1], O_RDONLY, 0777);
	if (fd_infile == -1)
	{
		ft_putstr_fd("Error opening infile\n ", 2);
		// return(-1);
		//exit(1);
	}
	printf("Je suis dans open_file avant de sortir\n");
	return (fd_infile);
}

int	open_outfile(char **argv)
{
	int	fd_outfile;

	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_outfile == -1)
	{
		ft_putstr_fd("Error opening outfile\n ", 2);
		// return (-1); ou exit(1); // a revoir
	}
	return (fd_outfile);
}
