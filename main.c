/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/03 17:36:42 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("pipe failed ");
		pid1 = child_first(fd, argv, envp);// creer le P enfant et execute la 1ere cmd
		pid2 = child_second(fd, argv, envp); // creer le 2e P enfant et execute la 2em cmd en lisant la sortie du 1er P via le pipe
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		ft_putstr_fd("Error\n./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}
