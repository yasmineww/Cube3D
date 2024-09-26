/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:06:10 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/21 10:13:18 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**free_mem(char **tab)
{
	unsigned int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
	return (NULL);
}

static size_t	skip_spaces(const char *s, size_t index)
{
	while (s[index] && (s[index] == ' ' || s[index] == '\t'))
		index++;
	return (index);
}

static char	*get_word(const char *s, size_t *index)
{
	size_t		start;
	size_t		len;
	char		*word;

	*index = skip_spaces(s, *index);
	start = *index;
	while (s[*index] && s[*index] != ' ' && s[*index] != '\t')
		(*index)++;
	len = *index - start;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = s[start + len];
	return (word);
}

char	**split_texture(char const *s)
{
	size_t	index;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	result[0] = get_word(s, &index);
	if (!result[0])
		return (free_mem(result));
	index = skip_spaces(s, index);
	if (s[index])
	{
		result[1] = ft_strdup(s + index);
		if (!result[1])
			return (free_mem(result));
	}
	else
	{
		result[1] = (char *)malloc(1 * sizeof(char));
		if (!result[1])
			return (free_mem(result));
		result[1][0] = '\0';
	}
	result[2] = NULL;
	return (result);
}