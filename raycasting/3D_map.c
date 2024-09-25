/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:53:56 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/25 19:11:28 by ymakhlou         ###   ########.fr       */
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
			ray_x =  data->player->x + (data->player->size / 2) + cos(data->player->rot_angle) * distance;
			ray_y =  data->player->y + (data->player->size / 2) + sin(data->player->rot_angle) * distance;
			mlx_put_pixel(data->mlx->img, ray_x, ray_y, 0x94F0ACFF);
		}
	}
}

float	normalize(float	angle, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 0 && angle < M_PI)
		ray->down = 1;
	// ray->down = (angle > 0 && angle < M_PI);
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		ray->left = 1;
	// ray->left = (angle > M_PI / 2 && angle < 3 * M_PI / 2);
	ray->up = !ray->down;
	ray->right = !ray->left;
	return (angle);
}

double	H_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;
	// double	distance_H;

	pos_y = (data->player->y / CUBE_SIZE + ray->down) * CUBE_SIZE;//why no floor
	pos_x = data->player->x + (pos_y - data->player->y) / tan(ray->ray_angle);
	ystep = CUBE_SIZE;
	if (data->ray->up)
		ystep *= -1;
	// ystep = CUBE_SIZE * (2 * data->ray->down - 1);//why not up
	xstep = fabs(CUBE_SIZE / tan(data->ray->ray_angle));
	if (data->ray->left)
		xstep *= -1;
	// xstep = fabs(CUBE_SIZE / tan(data->ray->ray_angle)) * (2 * data->ray->right - 1);
	while (!is_wall(data, pos_x, pos_y - data->ray->up))
	{
		pos_x += xstep;
		pos_y += ystep;
	}
	// distance_H = pos_x;
	pos_x -= data->player->x;
	pos_y -= data->player->y;
	return (hypot(pos_x, pos_y));
}

double	V_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;
	
	puts("V");
	pos_x = (data->player->x / CUBE_SIZE + ray->right) * CUBE_SIZE;
	pos_y = data->player->y + (pos_x - data->player->x) * tan(ray->ray_angle);
	xstep = CUBE_SIZE;
	if (data->ray->left)
		xstep *= -1;
	// xstep = CUBE_SIZE * (2 * data->ray->right - 1);//why not up
	ystep = fabs(CUBE_SIZE * tan(data->ray->ray_angle));
	if (data->ray->up)
		ystep *= -1;
	// ystep = fabs(CUBE_SIZE * tan(data->ray->ray_angle)) * (2 * data->ray->down - 1);
	while (!is_wall(data, pos_x - data->ray->left, pos_y))
	{
		pos_x += xstep;
		pos_y += ystep;
	}
	// distance_V = pos_y;
	pos_x -= data->player->x;
	pos_y -= data->player->y;
	return (hypot(pos_x, pos_y));
}


void	cast_one_ray(t_data *data, t_ray *ray)
{
	double	distance_H;
	double	distance_V;
	double	distance;

	ray->ray_angle = normalize(ray->ray_angle, ray);
	distance_H = H_intersect(data, ray);
	// distance_H = 10;
	distance_V = V_intersect(data, ray);
	distance = distance_H;
	if (distance_H > distance_V)
		distance = distance_V;
	draw_ray(data, distance);
	distance *= cos(ray->ray_angle - data->player->rot_angle);//fish eye
}

void	ray_casting(t_data *data)
{
	t_ray   *ray;
	int		i;

	i = 0;
	ray = data->ray;
	ray->ray_angle = data->player->rot_angle - (ray->pov / 2);
	while (ray->ray_angle < (ray->ray_angle + ray->pov))
	{
		cast_one_ray(data, ray);
		ray->ray_angle += i * (ray->pov / W_WIDTH);
		i++;
	}
}
