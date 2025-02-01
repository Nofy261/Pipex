/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:13:19 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/01 16:38:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> // open(),
# include <sys/types.h>
# include <sys/wait.h>

/*  utils.c */
char	**ft_split(char const *s, char c);



/* utils2.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

void	*free_all(char **str);

/* main.c */
char	**find_path(char **envp);
char	*get_path_complete(char **envp, char *cmd);
int		child_first(int *pipefd, char **argv, char **envp);
int		child_second(int *pipefd, char **argv, char **envp);
int		open_infile(char **argv);
int		open_outfile(char **argv);





















#endif 