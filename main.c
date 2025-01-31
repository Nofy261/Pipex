/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:26:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/01/31 16:12:46 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>


// char *pathname = get_path_complete(char **envp, char *av);
// execve(pathname, cmd, envp);


	
char	**find_path(char **envp) // doit return /bin ou /bin/bash sans les deux points entre eux
{
	int	i;
	char **path;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0) // path a ete trouvé
		{	
			path = ft_split(envp[i] + 5, ':'); // (MALLOC)
			return (path);
		}
		i++;
	}
	//if (!path)
	//	free(envp[i]);
	//free(envp);
	// exit + message d'erreur;
	return (NULL);
}
	
// doit return "/bin/ls" et sera envoyé a execve();	
char	*get_path_complete(char **envp, char *av)
{
	int	i;
	char **path;
	char *tmp;
	char **final_path;
	char **cmd;
	
	i = 0;
	//cmd = split_cmd(envp);
	path = find_path(envp);
	while (path[i]) // while (envp[i])??
	{
		tmp = ft_strjoin(path[i], '/'); // /bin sera /bin/ (MALLOC dans strjoin donc FREE)
		i++;
	}
	// if (access(cmd, X_OK) == 0)??
	cmd = ft_split(av, ' ');
	final_path = ft_strjoin(tmp, cmd[0]); // (MALLOC);
	free(tmp);
	return (final_path); // resultat = /bin/ls
}


	

execve("/bin/ls", av[2], NULL); // P child;
execve("/bin/wc", av[3], NULL); // P parent;


