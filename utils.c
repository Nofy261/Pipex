/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 09:15:44 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/03 15:54:50 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	counter;
	size_t	is_word;

	is_word = 0;
	i = 0;
	counter = 0;
	while (s[i])
	{
		if ((s[i] != c))
		{
			if (is_word == 0)
			{
				counter++;
				is_word = 1;
			}
		}
		else
			is_word = 0;
		i++;
	}
	return (counter);
}

void	*free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		// str[i] = NULL;
		i++;
	}
	free(str);
	//str = NULL;
	return (NULL);
}

static void	fill_result(char *new, char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
}

static void	set_mem(char **result, char const *str, char sep)
{
	size_t	count;
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (str[j])
	{
		count = 0;
		while (str[j + count] && str[j + count] != sep)
			count++;
		if (count > 0)
		{
			result[i] = malloc(sizeof(char) * (count + 1));
			if (!result[i])
				(free_all(result));
			fill_result(result[i], (str + j), sep);
			i++;
			j = j + count;
		}
		else
			j++;
	}
	result[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	set_mem(result, s, c);
	return (result);
}