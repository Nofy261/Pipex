/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:08:02 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/08 18:58:42 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// a tester chemin donné directement en commande comme argument
static int	execute_child1(int *pipefd, int infile_fd, char **argv, char **envp)
{
	char	**cmd_args;
	char	*path;

	close_dup_fd_child_first(pipefd, infile_fd);
	cmd_args = ft_split(argv[2], ' ');
	 // si pas de 1ere cmd , la 2em cmd ne se fera pas
	if (!cmd_args || !cmd_args[0])
	{
		free_all(cmd_args);
		ft_putstr_fd("cmd1 not found\n", 2);
		close(infile_fd);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(127);
		// return (-1);
	}
	path = get_path_complete(envp, cmd_args[0]);
	if (!path)
	{
		free_all(cmd_args);
		return (-1);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		ft_putstr_fd("First command failed\n", 2);
		free_all(cmd_args);
		free(path);
		return (-1);
	}
	return (0);
}

int	child_first(int *pipefd, char **argv, char **envp)
{
	pid_t	pid1;
	int		infile_fd;
	int exit_status;
	
	infile_fd = open_infile(argv);
	if (infile_fd == -1)
	{	
		// action??
		//exit(1);
	}
	pid1 = fork();
	if (pid1 == -1) // on quitte le programme en verifiant les fd ouvert avant;
	{
		ft_putstr_fd("fork failed 1\n", 2);
		// return (-1);
		close(infile_fd);
		exit(1);
	}
	if (pid1 == 0)
	{
		exit_status = execute_child1(pipefd, infile_fd, argv, envp);
		if (exit_status == -1)
		{
			ft_putstr_fd("Error in execute_child1 to find path\n", 2);
			// return ??
		}
	}
	close(infile_fd);
	return (pid1);
}

static void	execute_child2(int *pipefd, int outfile_fd, char **argv,
		char **envp)
{
	char	**cmd_args;
	char	*path;

	close_dup_fd_child_second(pipefd, outfile_fd);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args || !cmd_args[0])
	{
		free_all(cmd_args);
		ft_putstr_fd("cmd2 not found\n", 2);
		return ;
	}
	path = get_path_complete(envp, cmd_args[0]);
	if (!path)
	{
		free_all(cmd_args);
		ft_putstr_fd("Error in execute_child2 to find path\n", 2);
		return ;
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		perror("Second command failed ");
		free_all(cmd_args);
		free(path);
	}
}

int	child_second(int *pipefd, char **argv, char **envp)
{
	pid_t	pid2;
	int		outfile_fd;

	outfile_fd = open_outfile(argv);
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_putstr_fd("fork failed 2\n", 2);
		// return (-1); // on continue le programme
	}
	if (pid2 == 0)
	{
		execute_child2(pipefd, outfile_fd, argv, envp);
	}
	close(outfile_fd);
	return (pid2);
	// return (0);
}
