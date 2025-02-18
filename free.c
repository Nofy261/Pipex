/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:04:14 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/18 16:46:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all_paths(t_cmd *cmd)
{
	if (cmd->paths)
	{
		free_all(cmd->paths);
		cmd->paths = NULL;
	}
	if (cmd->good_paths1)
	{
		free_all(cmd->good_paths1);
		cmd->good_paths1 = NULL;
	}
	if (cmd->good_paths2)
	{
		free_all(cmd->good_paths2);
		cmd->good_paths2 = NULL;
	}
}

void	*free_all(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}
