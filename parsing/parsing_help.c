/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:42:49 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 22:26:23 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_map(t_list *parsing, char **map, int *old_rows, int *cols)
{
	t_map_create	arg;

	arg.max = 0;
	arg.new_rows = (*old_rows) - 2;
	arg.new_map = (char **)gc_malloc(&parsing->gc, \
		arg.new_rows * sizeof(char *));
	if (!arg.new_map)
		print_error(parsing, "Allocation Fails !\n");
	arg.i = 1;
	arg.row_index = 0;
	while (arg.i < *old_rows - 1)
	{
		arg.new_map[arg.row_index] = process_line(parsing, \
			map[arg.i], &arg.max, *cols);
		arg.row_index++;
		arg.i++;
	}
	arg.i = 0;
	*old_rows = arg.new_rows;
	*cols = arg.max;
	return (arg.new_map);
}

int	check_curr_char(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

void	get_player_position(t_list *parsing)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < parsing->rows)
	{
		while (y < parsing->cols)
		{
			if (check_curr_char(parsing->map[x][y]) == 1)
			{
				parsing->x = y;
				parsing->y = x;
			}
			y++;
		}
		x++;
		y = 0;
	}
}

t_door	*make_doors(int x, int y, t_list *parsing, int *c)
{
	t_door	*door;

	door = gc_malloc(&parsing->gc, sizeof(t_door));
	door->x = x;
	door->y = y;
	door->is_open = 0;
	door->next = NULL;
	(*c)++;
	return (door);
}

void	process_door(t_list *parsing, t_position_dor var, int *c, t_door **door)
{
	if (*c == 0)
	{
		parsing->doors = make_doors(var.x, var.y, parsing, c);
		*door = parsing->doors;
	}
	else
	{
		parsing->doors->next = make_doors(var.x, var.y, parsing, c);
		parsing->doors = parsing->doors->next;
	}
	if ((parsing->map[var.y - 1][var.x] != '1' \
		&& parsing->map[var.y + 1][var.x] != '1') &&
		(parsing->map[var.y][var.x + 1] != '1' && \
		parsing->map[var.y][var.x - 1] != '1'))
		print_error(parsing, "Invalid Door position!\n");
	check_door(parsing, var.x, var.y);
}
