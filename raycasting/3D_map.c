/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:53:56 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/27 16:16:36 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ray(t_data *data, double distance)
{
	int	i;
	int	ray_x;
	int	ray_y;

	i = -1;
	while (--distance >= 0)
	{
		{
			if (data->player->x < 0 || data->player->x > W_WIDTH || data->player->y < 0 || data->player->y > W_HEIGHT)
				return ;
			ray_x = data->player->x + cos(data->ray->ray_angle) * distance;
			ray_y = data->player->y + sin(data->ray->ray_angle) * distance;
			mlx_put_pixel(data->mlx->img, ray_x, ray_y, 0x94C8F0FF);
		}
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

double	h_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;
	// double	distance_h;

	pos_y = (data->player->y / CUBE_SIZE + ray->down) * CUBE_SIZE;
	pos_x = data->player->x + (pos_y - data->player->y) / tan(ray->ray_angle);
	ystep = CUBE_SIZE;
	if (data->ray->up)
		ystep *= -1;
	xstep = fabs(CUBE_SIZE / tan(data->ray->ray_angle));
	if (data->ray->left)
		xstep *= -1;
	while (!is_wall(data, pos_x, pos_y - data->ray->up))
	{
		pos_x += xstep;
		pos_y += ystep;
	}
	// distance_h = pos_x;
	pos_x -= data->player->x;
	pos_y -= data->player->y;
	return (hypot(pos_x, pos_y));
}

double	v_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;

	pos_x = (data->player->x / CUBE_SIZE + ray->right) * CUBE_SIZE;
	pos_y = data->player->y + (pos_x - data->player->x) * tan(ray->ray_angle);
	xstep = CUBE_SIZE;
	if (data->ray->left)
		xstep *= -1;
	ystep = fabs(CUBE_SIZE * tan(data->ray->ray_angle));
	if (data->ray->up)
		ystep *= -1;
	while (!is_wall(data, pos_x - data->ray->left, pos_y))
	{
		pos_x += xstep;
		pos_y += ystep;
	}
	// distance_v = pos_y;
	pos_x -= data->player->x;
	pos_y -= data->player->y;
	return (hypot(pos_x, pos_y));
}

void	cast_one_ray(t_data *data, t_ray *ray)
{
	double	distance_h;
	double	distance_v;
	double	distance;

	ray->ray_angle = normalize(ray->ray_angle, ray);
	distance_h = h_intersect(data, ray);
	// distance_h = 10;
	distance_v = v_intersect(data, ray);
	distance = distance_h;
	if (distance_h > distance_v)
		distance = distance_v;
	draw_ray(data, distance);
	// distance *= cos(ray->ray_angle - data->player->rot_angle);//fish eye
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	int		i;
	double	start;

	i = 1;
	ray = data->ray;
	start = data->player->rot_angle - (ray->pov / 2);
	ray->ray_angle = start;
	while (ray->ray_angle < (start + ray->pov))
	{
		cast_one_ray(data, ray);
		ray->ray_angle = start + i * (ray->pov / W_WIDTH);
		i++;
	}
}
