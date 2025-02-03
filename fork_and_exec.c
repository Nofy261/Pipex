/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:08:02 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/03 18:11:27 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void close_dup_fd_child_first(int *pipefd, int infile) // Rajout
{
	close(pipefd[0]);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}


int	child_first(int *pipefd, char **argv, char **envp)
{
	pid_t	pid1;
	char **cmd_args;
	char *path;
	int		infile;

	infile = open_infile(argv);
	pid1 = fork();
	if (pid1 == -1)
		perror("fork failed 1"); // rajouter return (-1)??
	if (pid1 == 0)
	{
		// close(pipefd[0]);
		// dup2(infile, STDIN_FILENO);
		// close(infile);
		// dup2(pipefd[1], STDOUT_FILENO);
		// close(pipefd[1]);
		close_dup_fd_child_first(pipefd, infile);
		cmd_args = ft_split(argv[2], ' ');// MALLOC
		path = get_path_complete(envp, cmd_args[0]);
		if (execve(path, cmd_args, envp) == -1)
		{
			free_all(cmd_args);
        	free(path);
			perror("First command can't be executed ");
		}
	}
	close(infile);
	return (pid1);
}

static void close_dup_fd_child_second(int *pipefd, int outfile) // Rajout
{
	close(pipefd[1]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
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
		perror("fork failed 2 ");// rajouter return (-1); ou exit direct?
	if (pid2 == 0)
	{
		// close(pipefd[1]);
		// dup2(outfile, STDOUT_FILENO);
		// close(outfile);
		// dup2(pipefd[0], STDIN_FILENO);
		// close(pipefd[0]);
		close_dup_fd_child_second(pipefd, outfile);// coupure rajout
		cmd_args = ft_split(argv[3], ' ');
		path = get_path_complete(envp, cmd_args[0]);
		if (execve(path, cmd_args, envp) == -1)
		{
			free_all(cmd_args);
        	free(path);
			perror("Second command can't be executed ");
		}
	}
	close(outfile);
	return (pid2);
}
