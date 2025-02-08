/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/08 19:01:43 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!envp || !envp[0])
	{
		ft_putstr_fd("Error : envp doesn't exist or is empty\n", 2);
		return (1);
	}
	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("pipe failed\n ", 2);
			return (1);
		}
		pid1 = child_first(fd, argv, envp);
		// if (pid1 == -1)
		// exit(-1);
		// return (1);
		pid2 = child_second(fd, argv, envp); // si pid2== -1? action?
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		ft_putstr_fd("Error : ./pipex infile cmd1 cmd2 outfile\n", 2);
	return (0);
}
