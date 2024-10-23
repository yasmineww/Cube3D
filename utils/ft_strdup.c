/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:00:05 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/22 14:03:59 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(const char *str, t_list *parsing_lst)
{
	int		i;
	char	*p;

	i = ft_strlen(str);
	p = (char *)gc_malloc(&parsing_lst->gc, i + 1 * 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
