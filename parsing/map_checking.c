/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:19:03 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/24 12:46:34 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_first_and_last(t_list *parsing_lst)
{
	int	i;
	int	j;
	int	c;

	i = 1;
	j = 1;
	c = 0;
	while (c < 2)
	{
		while (parsing_lst->map[i][j] == ' ' || parsing_lst->map[i][j] == '\t')
		{
			if (parsing_lst->map[i][j] == '\t')
				return (1);
			j++;
		}
		while (parsing_lst->map[i][j] == '1' || parsing_lst->map[i][j] == ' ')
			j++;
		if (parsing_lst->map[i][j] != '-')
			return (1);
		c++;
		i = parsing_lst->rows - 2;
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

int	check_start_end(t_list *parsing_lst)
{
	int	i;
	int	j;

	i = 2;
	j = 1;
	while (i < parsing_lst->rows - 2)
	{
		while (j < parsing_lst->cols - 1)
		{
			if (parsing_lst->map[i][j] == '0' || \
				parsing_lst->map[i][j] == 'S' || \
				parsing_lst->map[i][j] == 'N' || \
				parsing_lst->map[i][j] == 'W' || \
				parsing_lst->map[i][j] == 'E')
			{
				if (parsing_lst->map[i][j] != '0')
					parsing_lst->rot_angle = get_angle(parsing_lst->map[i][j]);
				if (parsing_lst->map[i][j - 1] == ' ' || \
					parsing_lst->map[i][j - 1] == '-' || \
					parsing_lst->map[i][j + 1] == ' ' || \
					parsing_lst->map[i][j + 1] == '-' || \
					parsing_lst->map[i - 1][j] == ' ' || \
					parsing_lst->map[i - 1][j] == '-' || \
					parsing_lst->map[i + 1][j] == ' ' || \
					parsing_lst->map[i + 1][j] == '-')
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
		c != ' ')
		return (1);
	return (0);
}

int check_unwanted_characters(t_list *parsing_lst)
{
	int	i;
	int	j;
	int	h;

	i = 1;
	j = 1;
	h = 0;
	while (i < parsing_lst->rows - 2)
	{
		while (j < parsing_lst->cols - 1)
		{
			if (check_char(parsing_lst->map[i][j]) == 1)
				return (1);
			if (parsing_lst->map[i][j] == 'N' || \
				parsing_lst->map[i][j] == 'W' || \
				parsing_lst->map[i][j] == 'E' || parsing_lst->map[i][j] == 'S')
				h++;
			j++;
		}
		j = 1;
		i++;
	}
	if (h > 1 || h == 0)
		return (1);
	return (0);
}

int	check_map(t_list *parsing_lst)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (check_first_and_last(parsing_lst) == 1)
		return (1);
	if (check_unwanted_characters(parsing_lst) == 1)
		return (1);
	if (check_start_end(parsing_lst) == 1)
		return (1);
	return (0);
}
