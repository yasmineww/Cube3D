/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:06:07 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 05:05:32 by youbihi          ###   ########.fr       */
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

static size_t	ft_countword(char const *s)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i])
			wc++;
		while (s[i] && (s[i] != ' ' && s[i] != '\t'))
			i++;
	}
	return (wc);
}

static char	*words_len(const char *s, size_t *w)
{
	char		*word;
	size_t		len;
	size_t		i;
	size_t		j;

	len = 0;
	j = 0;
	while (s[*w] && (s[*w] == ' ' || s[*w] == '\t'))
		(*w)++;
	i = *w;
	while (s[*w] && (s[*w] != ' ' && s[*w] != '\t'))
		(*w)++;
	len = *w - i;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (i + j < *w)
	{
		word[j] = s[i + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_custom_split(char const *s)
{
	size_t	word;
	char	**str;
	size_t	w;
	size_t	id;

	if (!s)
		return (NULL);
	word = ft_countword(s);
	str = (char **)malloc((word + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	w = 0;
	id = 0;
	while (w < word)
	{
		str[w] = words_len(s, &id);
		if (!str[w])
			return (free_mem(str));
		w++;
	}
	str[word] = NULL;
	return (str);
}
