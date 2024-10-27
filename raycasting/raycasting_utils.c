/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:08:15 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/27 21:04:11 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ray(t_data *data, double distance)
{
	int		ray_x;
	int		ray_y;

	while (--distance >= 0)
	{
		ray_x = (M_WIDTH / 2 + cos(data->ray->ray_angle) * distance);
		ray_y = (M_HEIGHT / 2 + sin(data->ray->ray_angle) * distance);
		if (ray_x < 0 || ray_x >= M_WIDTH || ray_y < 0 || ray_y >= M_HEIGHT)
			continue ;
		mlx_put_pixel(data->mlx->img, ray_x, ray_y, 0xFFFF72FF);
	}
}

float	normalize(float angle, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 0 && angle < M_PI)
		ray->down = 1;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		ray->left = 1;
	ray->up = !ray->down;
	ray->right = !ray->left;
	return (angle);
}

int	door_open(int x, int y, t_data *data)
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

int	is_wall(t_data *data, double x, double y)
{
	int	index_x;
	int	index_y;

	index_x = x / CUBE_SIZE;
	index_y = y / CUBE_SIZE;
	if (index_x < 0 || index_x >= data->cols || index_y < 0
		|| index_y >= data->rows || data->map[index_y][index_x] == '1')
		return (1);
	else if ((index_x < 0 || index_x >= data->cols || index_y < 0 || \
		index_y >= data->rows || \
		data->map[index_y][index_x] == 'D') && \
		door_open(index_x, index_y, data) != 1)
		return (2);
	return (0);
}

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < CUBE_SIZE)
	{
		j = -1;
		while (++j < CUBE_SIZE)
		{
			if ((j + x) >= 0 && (i + y) >= 0 && (j + x) < M_WIDTH
				&& (i + y) < M_HEIGHT)
				mlx_put_pixel(data->mlx->img, (j + x), (i + y), color);
		}
	}
}
