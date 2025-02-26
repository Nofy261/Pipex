/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:13:19 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/19 08:25:48 by nolecler         ###   ########.fr       */
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

typedef struct s_cmd
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		fd_infile;
	int		fd_outfile;
	int		error_infile;
	int		error_outfile;
	char	**good_paths1;
	char	**good_paths2;
	char	*infile;
	char	*outfile;
	char	**paths;
	char	*tmp;
	char	**full_cmd;
	char	*is_valid_cmd;
}			t_cmd;

void		close_fds(t_cmd *cmd);
void		close_and_free(t_cmd *cmd);

void		process_start(t_cmd *cmd, char **envp);

void		free_all_paths(t_cmd *cmd);
void		*free_all(char **str);

void		init_struct(t_cmd *cmd);

char		**ft_split(char const *s, char c);

char		**find_path(char **envp);
char		**get_path_complete(t_cmd *cmd, char **path, char *command);

int			open_files(t_cmd *cmd, char **argv);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr_fd(char *str, int fd);
int			check_envp(char **envp);

char		**get_valid_paths(t_cmd *cmd, char **envp);

void		initialize_pipe(t_cmd *cmd);
void		validate_command(t_cmd *cmd, char **argv, int *exit_code);

#endif