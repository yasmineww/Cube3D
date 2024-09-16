/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:09:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/12 16:56:06 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../cub3d.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
