/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/01 17:16:26 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>



int	child_first(int *pipefd, char **argv, char **envp)
{
	pid_t	pid1;
	char **cmd_args;
	char *path;
	int		infile;

	infile = open_infile(argv);
	pid1 = fork();
	if (pid1 == -1)
		//fork_error();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		cmd_args = ft_split(argv[2], ' ');
		path = get_path_complete(envp, cmd_args[0]);
		execve(path, cmd_args, envp);
		// {
		// 	perror("execve failed");
        // 	free(path);
        // 	return (1);
		// }
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
		//fork_error();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		cmd_args = ft_split(argv[3], ' ');
		path = get_path_complete(envp, cmd_args[0]);
		execve(path, cmd_args, envp);
		// {
		// 	perror("execve failed");
        // 	free(path);
        // 	return (1);
		// }
	}
	close(outfile);
	return (pid2);
}

int	open_infile(char **argv)
{
	int	fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror("Error opening infile : ");
		return(1);
	}
	return (0);
}
int	open_outfile(char **argv)
{
	int fd_outfile;
	
	fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_outfile == -1)
	{
		perror("Error opening outfile ");
		return (1);
	}
	return (0);
}


char	**find_path(char **envp)
{
	int	i;
	char **path;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{	
			path = ft_split(envp[i] + 5, ':'); // (MALLOC)
			return (path);
		}
		i++;
	}
	// exit + message d'erreur;
	return (NULL);
}
	
// doit return "/bin/ls" et sera envoyé a execve();	
char	*get_path_complete(char **envp, char *cmd)
{	
	//int j;
	int	i;
	char **path;
	char *tmp;
	char *final_path;
	
	//j = 0;
	i = 0;
	
	path = find_path(envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/"); // /bin sera /bin/ (MALLOC dans strjoin donc FREE)
		final_path = ft_strjoin(tmp, cmd); // (MALLOC);
		free(tmp);
		if (access(final_path, X_OK ) == 0)
		{
			// while(path[j])
			// {
			// 	free(path[j]);
			// 	j++;
			// }
			// free(path);
			return (final_path);
		}	
		free(final_path);
		i++;
	}
	free_all(path);
	return (NULL);
}


int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			// message d erreur
			printf("Erreur fd = -1\n");
		pid1 = child_first(fd, argv, envp);
		pid2 = child_second(fd, argv, envp);
		if (pid1 == 1)
			return (pid1);
		if (pid2 == 1)
			return (pid2);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
		// message erreur 
		printf("Erreur fin\n");
	return (0);
}