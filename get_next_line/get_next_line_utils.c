/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:27:03 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/22 14:33:59 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_line_len(char *str)
{
	int	i;
	int	back_slash_zero_count;

	i = 0;
	back_slash_zero_count = 0;
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			back_slash_zero_count++;
		i++;
	}
	return (i - back_slash_zero_count);
}

int	count_len_for_left(char *str)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[i] != '\n')
		i++;
	while (str[i + index])
		index++;
	return (index);
}

char	*ft_left_lines(char *all_lines, t_list *parsing)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (all_lines[i] && all_lines[i] != '\n')
		i++;
	if (!all_lines[i])
	{
		free(all_lines);
		return (NULL);
	}
	temp = (char *)gc_malloc(&parsing->gc, sizeof(char) * \
		(ft_strlen_get(all_lines) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (all_lines[i])
		temp[j++] = all_lines[i++];
	temp[j] = '\0';
	free(all_lines);
	return (temp);
}

char	*ft_allocate_joined_string(char *left_str, char *buff, t_list *parsing)
{
	char	*str;

	if (!left_str)
	{
		left_str = (char *)gc_malloc(&parsing->gc, 1 * sizeof(char));
		if (left_str == NULL)
			return (NULL);
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = gc_malloc(&parsing->gc, sizeof(char) * \
		((ft_strlen_get(left_str) + ft_strlen_get(buff)) + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*ft_strjoin_get(char *left_str, char *buff, t_list *parsing)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = ft_allocate_joined_string(left_str, buff, parsing);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (left_str)
	{
		while (left_str[i] != '\0')
		{
			str[i] = left_str[i];
			i++;
		}
	}
	while (buff[j] != '\0')
	{
		str[i++] = buff[j++];
	}
	str[i] = '\0';
	free(left_str);
	return (str);
}

