/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:01:17 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/22 16:37:34 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wc++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wc);
}

static char	*words_len(const char *s, char c, size_t *w, t_list *parsing_lst)
{
	char		*word;
	size_t		len;
	size_t		i;
	size_t		j;

	len = 0;
	j = 0;
	while (s[*w] && s[*w] == c)
		(*w)++;
	i = *w;
	while (s[*w] && s[*w] != c)
		(*w)++;
	len = *w - i;
	word = (char *)gc_malloc(&parsing_lst->gc, (len + 1) * sizeof(char));
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

char	**ft_split(char const *s, char c, t_list *parsing_lst)
{
	size_t	word;
	char	**str;
	size_t	w;
	size_t	id;

	if (!s)
		return (NULL);
	word = ft_countword(s, c);
	str = (char **)gc_malloc(&parsing_lst->gc, (word + 1) * sizeof(char *));
	if (!str)
		print_error("Allocation Fails !\n");
	w = 0;
	id = 0;
	while (w < word)
	{
		str[w] = words_len(s, c, &id, parsing_lst);
		w++;
	}
	str[word] = NULL;
	return (str);
}
