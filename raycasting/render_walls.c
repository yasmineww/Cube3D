/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:40:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/28 15:47:15 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*get_horizontal_texture(t_data *data)
{
	if (data->ray->ray_angle > 0 && data->ray->ray_angle < M_PI)
	{
		if (data->ray->door == 1)
			return (data->mlx->door);
		return (data->mlx->so);
	}
	else
	{
		if (data->ray->door == 1)
			return (data->mlx->door);
		return (data->mlx->no);
	}
}

mlx_texture_t	*get_curr_texture(t_data *data)
{
	data->ray->ray_angle = normalize(data->ray->ray_angle, data->ray);
	if (data->ray->is_v == 1)
		return (get_vertical_texture(data));
	else
		return (get_horizontal_texture(data));
}

void	calculate_wall_dimensions(t_data *data, double distance, \
	int nmbr_rays, t_wall_var *value)
{
	value->var.texture = get_curr_texture(data);
	value->wall_height = (CUBE_SIZE / distance) * \
		(W_WIDTH / 2) / tan(data->ray->pov / 2);
	value->top = (W_HEIGHT / 2) - (value->wall_height / 2);
	value->bot = (W_HEIGHT / 2) + (value->wall_height / 2);
	if (value->bot > W_HEIGHT)
		value->bot = W_HEIGHT;
	if (value->top < 0)
		value->top = 0;
	render_bottom(data, nmbr_rays, value->bot);
	render_top(data, nmbr_rays, value->top);
}

void	render_wall_texture(t_data *data, int nmbr_rays, t_wall_var *value)
{
	value->var.factor = (double)value->var.texture->height / value->wall_height;
	value->var.arr = (int *)value->var.texture->pixels;
	value->var.x_offset = get_x_offset(value->var.texture, data);
	value->var.y_offset = (value->top - (W_HEIGHT / 2) + \
		(value->wall_height / 2)) * value->var.factor;
	if (value->var.y_offset < 0)
		value->var.y_offset = 0;
	while (value->top < value->bot)
	{
		if (nmbr_rays >= M_WIDTH || value->top >= M_HEIGHT)
		{
			mlx_put_pixel(data->mlx->img, nmbr_rays, value->top,
				reverse(value->var.arr[(int)value->var.y_offset * value->var.texture->width + (int)value->var.x_offset]));
		}
		value->var.y_offset += value->var.factor;
		value->top++;
	}
}

void	render_wall(t_data *data, double distance, int nmbr_rays)
{
	t_wall_var	value;

	calculate_wall_dimensions(data, distance, \
		nmbr_rays, &value);
	render_wall_texture(data, nmbr_rays, &value);
}
