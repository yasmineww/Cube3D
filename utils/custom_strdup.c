/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:09:31 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/26 20:31:05 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_custom_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_custom_strdup(const char *str)
{
	int		i;
	char	*p;

	i = ft_custom_strlen(str);
	p = (char *)malloc(i + 1 * 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (str && str[i] && str[i] != '\n')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
