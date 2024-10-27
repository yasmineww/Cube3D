/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:53:56 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/27 21:03:19 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_door(t_data *data, double pos_x, double pos_y, int index)
{
	int	res;

	res = is_wall(data, pos_x, pos_y);
	if (index == 1)
	{
		if (res == 2 && data->open != 1)
		{
			data->ray->door_h = 1;
			return (1);
		}
	}
	else if (index == 2)
	{
		if (res == 2 && data->open != 1)
		{
			data->ray->door_v = 1;
			return (1);
		}
	}
	return (0);
}

double	h_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;

	data->ray->door_h = 0;
	ystep = CUBE_SIZE;
	if (data->ray->up)
		ystep *= -1;
	xstep = fabs(CUBE_SIZE / tan(data->ray->ray_angle));
	if (data->ray->left)
		xstep *= -1;
	pos_y = (data->player->y / CUBE_SIZE + ray->down) * CUBE_SIZE;
	pos_x = data->player->x + (pos_y - data->player->y) / tan(ray->ray_angle);
	while (is_wall(data, pos_x, pos_y - data->ray->up) != 1)
	{
		if (is_door(data, pos_x, pos_y - data->ray->up, 1))
			break ;
		pos_x += xstep;
		pos_y += ystep;
	}
	ray->distance_h = pos_x;
	return (hypot(pos_x - data->player->x, pos_y - data->player->y));
}

double	v_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;

	data->ray->door_v = 0;
	xstep = CUBE_SIZE;
	if (data->ray->left)
		xstep *= -1;
	ystep = fabs(CUBE_SIZE * tan(data->ray->ray_angle));
	if (data->ray->up)
		ystep *= -1;
	pos_x = (data->player->x / CUBE_SIZE + ray->right) * CUBE_SIZE;
	pos_y = data->player->y + (pos_x - data->player->x) * tan(ray->ray_angle);
	while (is_wall(data, pos_x - data->ray->left, pos_y) != 1)
	{
		if (is_door(data, pos_x - data->ray->left, pos_y, 2))
			break ;
		pos_x += xstep;
		pos_y += ystep;
	}
	ray->distance_v = pos_y;
	return (hypot(pos_x - data->player->x, pos_y - data->player->y));
}

void	cast_one_ray(t_data *data, int nmbr_rays)
{
	t_ray	*ray;
	double	distance_h;
	double	distance_v;
	double	distance;

	data->ray->door = 0;
	ray = data->ray;
	ray->ray_angle = normalize(ray->ray_angle, ray);
	distance_h = h_intersect(data, ray);
	distance_v = v_intersect(data, ray);
	distance = distance_h;
	data->ray->door = data->ray->door_h;
	ray->is_v = 0;
	if (distance_h > distance_v)
	{
		data->ray->door = data->ray->door_v;
		distance = distance_v;
		ray->is_v = 1;
	}
	draw_ray(data, distance);
	distance *= cos(ray->ray_angle - data->player->view_angle);
	render_wall(data, distance, nmbr_rays);
}

void	ray_casting(t_data *data)
{
	t_ray	*ray;
	int		nmbr_rays;

	nmbr_rays = 0;
	ray = data->ray;
	ray->ray_angle = data->player->view_angle - (ray->pov / 2);
	while (nmbr_rays < W_WIDTH)
	{
		cast_one_ray(data, nmbr_rays);
		ray->ray_angle += (ray->pov / W_WIDTH);
		nmbr_rays++;
	}
	draw_sprite(data);
}
