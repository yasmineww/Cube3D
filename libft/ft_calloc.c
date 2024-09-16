/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:48:30 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/12 16:56:06 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../cub3d.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc(nmemb * size);
	if (p == NULL)
	{
		return (NULL);
	}
	while (i < size * nmemb)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
