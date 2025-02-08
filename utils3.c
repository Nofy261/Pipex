/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:54:38 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/08 19:02:30 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_dup_fd_child_first(int *pipefd, int infile_fd)
{
	close(pipefd[0]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

void	close_dup_fd_child_second(int *pipefd, int outfile_fd)
{
	close(pipefd[1]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	*free_and_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

// void	close_fd(int fd)
// {
// 	if (fd && fd > 2)
// 		close(fd);
// }