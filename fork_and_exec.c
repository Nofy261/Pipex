/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:08:02 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/03 14:22:04 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_first(int *pipefd, char **argv, char **envp)
{
	pid_t	pid1;
	char **cmd_args;
	char *path;
	int		infile;

	infile = open_infile(argv);
	pid1 = fork();
	if (pid1 == -1)
		error();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		cmd_args = ft_split(argv[2], ' ');
		path = get_path_complete(envp, cmd_args[0]);
		if (execve(path, cmd_args, envp) == -1)
		{
			error();
        // 	free(path);
        // 	return (1);
		}
	}
	close(infile);
	return (pid1);
}

int	child_second(int *pipefd, char **argv, char **envp)
{
	pid_t	pid2;
	char **cmd_args;
	char *path;
	int		outfile;

	outfile = open_outfile(argv);
	pid2 = fork();
	if (pid2 == -1)
		error();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		cmd_args = ft_split(argv[3], ' ');
		path = get_path_complete(envp, cmd_args[0]);
		if (execve(path, cmd_args, envp) == -1)
		{
			error();
        // 	free(path);
        // 	return (1);
		}
	}
	close(outfile);
	return (pid2);
}
