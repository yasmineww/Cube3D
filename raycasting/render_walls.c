/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:40:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/04 18:09:29 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	render_bot_top(t_data *data, int nmbr_rays, double bot, double top)
{
	int		i;

	i = bot;
	while (i < W_HEIGHT)
	{
		if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && top >= 0 && top < W_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0X828282);
		i++;
	}
	i = 0;
	while (i < top)
	{
		if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && top >= 0 && top < W_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0x89CFF3FF);
		i++;
	}
}

double	get_x_offset(mlx_texture_t	*ea, t_data *data)
{
	double	x_offeset;

	if (data->ray->is_v == 1)
		x_offeset = (int)fmod(data->ray->distance_v * \
			(ea->width / CUBE_SIZE), ea->width);
	else
		x_offeset = (int)fmod(data->ray->distance_h * \
		(ea->width / CUBE_SIZE), ea->width);
	return (x_offeset);
}

mlx_texture_t	*get_curr_texture(t_data *data)
{
	data->ray->ray_angle = normalize(data->ray->ray_angle, data->ray);
	if (data->ray->is_v == 1)
	{
		if (data->ray->ray_angle > M_PI / 2 && \
			data->ray->ray_angle < 3 * (M_PI / 2))
			return (data->open_textures->ea);
		else
			return (data->open_textures->we);
	}
	else
	{
		if (data->ray->ray_angle > 0 && data->ray->ray_angle < M_PI)
			return (data->open_textures->so);
		else
			return (data->open_textures->no);
	}
}

void	render_wall(t_data *data, double distance, int nmbr_rays)
{
	t_wall_render	var;

	var.the_texture = get_curr_texture(data);
	var.ray = data->ray;
	var.wall_height = (CUBE_SIZE / distance) * (W_WIDTH / 2) / tan(var.ray->pov / 2);
	var.top = (W_HEIGHT / 2) - (var.wall_height / 2);
	var.bot = (W_HEIGHT / 2) + (var.wall_height / 2);
	if (var.bot > W_HEIGHT)
		var.bot = W_HEIGHT;
	if (var.top < 0)
		var.top = 0;
	render_bot_top(data, nmbr_rays, var.bot, var.top);
	var.factor = (double) var.the_texture->height / var.wall_height;
	var.arr = (int *)var.the_texture->pixels;
	var.x_offset = get_x_offset(var.the_texture, data);
	var.y_offset = (var.top - (W_HEIGHT / 2) + (var.wall_height / 2)) * var.factor;
	if (var.y_offset < 0)
		var.y_offset = 0;
	while (var.top < var.bot)
	{
		mlx_put_pixel(data->mlx->img, nmbr_rays, var.top, reverse_bytes(var.arr[(int) var.y_offset * var.the_texture->width + (int)var.x_offset]));
		var.y_offset += var.factor;
		var.top++;
	}
}
