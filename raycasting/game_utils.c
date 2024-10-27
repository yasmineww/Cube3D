/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:56:34 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/27 20:56:45 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	door_is_open(int y, int x, t_data *data)
{
	t_door	*door;

	door = data->doors;
	while (door)
	{
		if (door->y == y && door->x == x)
		{
			if (door->is_open == 1)
			{
				return (1);
			}
		}
		door = door->next;
	}
	return (0);
}

int	check_wall(t_data *data, t_wall_collision var)
{
	if (var.x_min < 0 || var.x_max >= data->cols || \
		var.y_min < 0 || var.y_max >= data->rows
		|| data->map[var.y_min][var.x_min] == '1'
		|| data->map[var.y_max][var.x_max] == '1'
		|| data->map[var.y_max][var.x_min] == '1'
		|| data->map[var.y_min][var.x_max] == '1')
		return (1);
	if ((data->map[var.y_min][var.x_min] == 'D' || \
		data->map[var.y_max][var.x_max] == 'D'
		|| data->map[var.y_max][var.x_min] == 'D' || \
		data->map[var.y_min][var.x_max] == 'D')
		&& (door_is_open(var.y_min, var.x_min, data) != 1
		&& door_is_open(var.y_max, var.x_max, data) != 1
		&& door_is_open(var.y_max, var.x_min, data) != 1
		&& door_is_open(var.y_min, var.x_max, data) != 1))
		return (1);
	return (0);
}

int	wall_collision(t_data *data, double x, double y)
{
	t_wall_collision	var;

	var.x_min = (x - data->player->rayon) / CUBE_SIZE;
	var.x_max = (x + data->player->rayon) / CUBE_SIZE;
	var.y_min = (y - data->player->rayon) / CUBE_SIZE;
	var.y_max = (y + data->player->rayon) / CUBE_SIZE;
	return (check_wall(data, var));
}

void	move_player(t_player *player, t_data *data)
{
	int		x;
	int		y;
	double	angle;

	angle = player->view_angle + player->walk + player->turn;
	x = roundf(player->x + player->move_speed * cos(angle));
	y = roundf(player->y + player->move_speed * sin(angle));
	if (!wall_collision(data, x, y))
	{
		if (player->turn || player->walk)
		{
			player->x = x;
			player->y = y;
		}
	}
}

void	create_player(t_data *data)
{
	t_player	*player;
	int			size;
	int			i;
	int			j;

	size = 8;
	player = data->player;
	i = size * -1;
	while (i <= size)
	{
		j = size * -1;
		while (j <= size)
		{
			if (j * j + i * i <= size * size)
				mlx_put_pixel(data->mlx->img, (j + M_WIDTH / 2),
					(i + M_HEIGHT / 2), 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}
