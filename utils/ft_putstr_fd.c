/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:16:34 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/20 15:42:04 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	if (fd >= 0)
	{
		i = 0;
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}
