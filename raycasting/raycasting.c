/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:53:56 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/13 19:19:45 by ymakhlou         ###   ########.fr       */
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
		if (ray_x < 0 || ray_x > M_WIDTH || ray_y < 0 || ray_y > M_HEIGHT)
			continue ;
		mlx_put_pixel(data->mlx->img, ray_x, ray_y, 0x94C8F0FF);
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

	ystep = CUBE_SIZE;
	if (data->ray->up)
		ystep *= -1;
	xstep = fabs(CUBE_SIZE / tan(data->ray->ray_angle));
	if (data->ray->left)
		xstep *= -1;
	pos_y = (data->player->y / CUBE_SIZE + ray->down) * CUBE_SIZE;
	pos_x = data->player->x + (pos_y - data->player->y) / tan(ray->ray_angle);
	while (!is_wall(data, pos_x, pos_y - data->ray->up))
	{
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

	xstep = CUBE_SIZE;
	if (data->ray->left)
		xstep *= -1;
	ystep = fabs(CUBE_SIZE * tan(data->ray->ray_angle));
	if (data->ray->up)
		ystep *= -1;
	pos_x = (data->player->x / CUBE_SIZE + ray->right) * CUBE_SIZE;
	pos_y = data->player->y + (pos_x - data->player->x) * tan(ray->ray_angle);
	while (!is_wall(data, pos_x - data->ray->left, pos_y))
	{
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
	ray->is_v = 0;
	if (distance_h > distance_v)
		{
			distance = distance_v;
			ray->is_v = 1;
		}
	draw_ray(data, distance);
	distance *= cos(ray->ray_angle - data->player->view_angle);//fish eye
	render_wall(data, distance, nmbr_rays);
}

void	ray_casting(t_data *data)
{
	t_ray			*ray;
	int				nmbr_rays;

	nmbr_rays = 0;
	ray = data->ray;
	ray->ray_angle = data->player->view_angle - (ray->pov / 2);
	load_textures(data);
	while (nmbr_rays < W_WIDTH)
	{
		cast_one_ray(data, nmbr_rays);
		ray->ray_angle += (ray->pov / W_WIDTH);
		nmbr_rays++;
	}
	draw_texture_with_put_pixel(data, 2);//name shouldnt have more than 3 words
}
