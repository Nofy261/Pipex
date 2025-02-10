/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:13:19 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/10 15:40:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
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
	char	**good_paths1;
	char	**good_paths2;
	char	*infile;
	char	*outfile;
	char	**paths;
	char	*tmp;
	char	**full_cmd;
	char	*is_valid_cmd;
}			t_cmd;


/* close_fd.c */
void	close_fds(t_cmd *cmd);
void	close_and_free(t_cmd *cmd);

/* fork_and_exec.c */
void	process_start(t_cmd *cmd, char **envp);

/* free.c */
void	free_all_paths(t_cmd *cmd);
void	*free_all(char **str);

/* init_struc.c*/
void	init_struct(t_cmd *cmd);

/*  ft_split.c */
char	**ft_split(char const *s, char c);

/* get_path.c */
char	**find_path(char **envp);
char	**get_path_complete(t_cmd *cmd, char **path, char *command);


/* open_file.c */
void	open_files(t_cmd *cmd, char **argv);

/* utils.c*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *str, int fd);
int		check_envp(char **envp);

/* verif.c */
char	**get_valid_paths(char **envp);
int		validate_commands(t_cmd *cmd, char **argv);
int		initialize_pipe(t_cmd *cmd);
int		error_command_null(t_cmd *cmd, char **command_path,
			char *error_message);


#endif