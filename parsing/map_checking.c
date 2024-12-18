/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:19:03 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/29 21:30:19 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_first_and_last(t_list *parsing)
{
	int	i;
	int	j;
	int	c;

	i = 1;
	j = 1;
	c = 0;
	while (c < 2)
	{
		while (parsing->map[i][j] == ' ' || parsing->map[i][j] == '\t')
		{
			if (parsing->map[i][j] == '\t')
				return (1);
			j++;
		}
		while (parsing->map[i][j] == '1' || parsing->map[i][j] == ' ')
			j++;
		if (parsing->map[i][j] != '-')
			return (1);
		c++;
		i = parsing->rows - 2;
		j = 1;
	}
	return (0);
}

double	get_angle(char c)
{
	if (c == 'N')
		return (3 * M_PI / 2);
	else if (c == 'S')
		return (M_PI / 2);
	else if (c == 'E')
		return (0);
	else
		return (M_PI);
}

int	check_character(char c)
{
	if (c == '0' || \
		c == 'S' || \
		c == 'N' || \
		c == 'W' || \
		c == 'E')
	{
		return (1);
	}
	return (0);
}

int	check_start_end(t_list *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lst->rows - 2)
	{
		while (j < lst->cols - 1)
		{
			if (check_character(lst->map[i][j]) == 1)
			{
				if (lst->map[i][j] != '0')
					lst->view_angle = get_angle(lst->map[i][j]);
				if (lst->map[i][j - 1] == ' ' || lst->map[i][j - 1] == '-' || \
					lst->map[i][j + 1] == ' ' || lst->map[i][j + 1] == '-' || \
					lst->map[i - 1][j] == ' ' || lst->map[i - 1][j] == '-' || \
					lst->map[i + 1][j] == ' ' || lst->map[i + 1][j] == '-')
					return (1);
			}
			j++;
		}
		i++;
		j = 1;
	}
	return (0);
}

int	check_char(char c)
{
	if (c != '0' && \
		c != '1' && \
		c != 'N' && \
		c != 'W' && \
		c != 'E' && \
		c != 'S' && \
		c != ' ' && \
		c != 'D'
	)
		return (1);
	return (0);
}
