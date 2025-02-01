/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/01 11:07:19 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>


char	**find_path(char **envp)
{
	int	i;
	char **path;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
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
	int j;
	int	i;
	char **path;
	char *tmp;
	char *final_path;
	
	j = 0;
	i = 0;
	path = find_path(envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/"); // /bin sera /bin/ (MALLOC dans strjoin donc FREE)
		final_path = ft_strjoin(tmp, cmd); // (MALLOC);
		free(tmp);
		if (access(final_path, X_OK) == 0)
		{
			while(path[j])
			{
				free(path[j]);
				j++;
			}
			free(path);
			return (final_path);
		}	
		free(final_path);
		i++;
	}
	return (NULL);
}



int main(int argc, char **argv, char **envp)
{
	(void)argc;
	char **cmd_args;
    char *pathname;
	
	cmd_args = ft_split(argv[1], ' ');
	pathname = get_path_complete(envp, cmd_args[0]);
	if (!pathname)
	{
		printf("Error : command not found\n");
	}
	if (execve(pathname, cmd_args, envp) == -1)
	{
		perror("execve failed");
        free(pathname);
        return (1);
	}
	free(pathname);
	return (0);	
}


