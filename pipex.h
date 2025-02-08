/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:13:19 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/08 19:02:54 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/*  utils1.c */
char	**ft_split(char const *s, char c);
void	*free_all(char **str);

/* utils2.c */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/* utils3.c */
void	close_dup_fd_child_first(int *pipefd, int infile_fd);
void	close_dup_fd_child_second(int *pipefd, int outfile_fd);
void	*free_and_null(void *ptr);
void	ft_putstr_fd(char *str, int fd);

/* get_path.c */
char	**find_path(char **envp);
char	*get_path_complete(char **envp, char *cmd);

/* fork_and_exec.c */
int		child_first(int *pipefd, char **argv, char **envp);
int		child_second(int *pipefd, char **argv, char **envp);

/* open_file.c */
int		open_infile(char **argv);
int		open_outfile(char **argv);

#endif