/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:04:50 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/12 16:56:06 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../cub3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		b;
	char	*new;
	int		c;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	b = ft_strlen(s2);
	c = 0;
	new = (char *)malloc(b + i + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, (char *) s1, i);
	ft_memcpy(new + i, (char *) s2, b);
	new[i + b] = '\0';
	return (new);
}
