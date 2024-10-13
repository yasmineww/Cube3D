/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:40:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/13 19:29:29 by ymakhlou         ###   ########.fr       */
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

double	get_x_offset(mlx_texture_t *ea, t_data *data)
{
	double	x_offeset;

	if (data->ray->is_v == 1)
		x_offeset = (int)fmod(data->ray->distance_v * (ea->width / CUBE_SIZE), ea->width);
	else
		x_offeset = (int)fmod(data->ray->distance_h * (ea->width / CUBE_SIZE), ea->width);
	return (x_offeset);
}

void	render_bot_top(t_data *data, int nmbr_rays, double bot, double top)
{
	int	i;
	int	rand_num;
	int	c;

	i = bot;
	while (i < W_HEIGHT)
	{
		if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && top >= 0 && top < W_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0x555555);
		i++;
	}
	i = 0;
	while (i < top)
	{
		if (nmbr_rays >= M_WIDTH || i >= M_HEIGHT)
		{
			rand_num = rand() % 100;
			c = -1;
			if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && top >= 0 && top < W_HEIGHT)
			{
				if (rand_num == 0)
				{
					while (i++ < top && ++c < 4)
						mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0xFFFF00);
				}
				else
					mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0x0000FF);
			}	
		}
		i++;
	}
}

mlx_texture_t	*get_curr_texture(t_data *data)
{
	data->ray->ray_angle = normalize(data->ray->ray_angle, data->ray);
	printf("%d\n",data->ray->door);
	if (data->ray->is_v == 1)
	{
		if (data->ray->ray_angle > M_PI / 2 && \
			data->ray->ray_angle < 3 * (M_PI / 2))
			{
				if (data->ray->door == 1)
				{
					return (data->mlx->door);
				}
				return (data->mlx->ea);
			}
		else
		{
			if (data->ray->door == 1)
			{
				return (data->mlx->door);
			}
			return (data->mlx->we);
		}
	}
	else
	{
		if (data->ray->ray_angle > 0 && data->ray->ray_angle < M_PI)
		{
			if (data->ray->door == 1)
			{
				return (data->mlx->door);
			}
			return (data->mlx->so);
		}
		else
		{
			if (data->ray->door == 1)
			{
				return (data->mlx->door);
			}
			return (data->mlx->no);
		}
	}
}

void	render_wall(t_data *data, double distance, int nmbr_rays)
{
	t_wall_render	var;
	double			top;
	double			bot;
	double			wall_height;

	var.texture = get_curr_texture(data);
	wall_height = (CUBE_SIZE / distance) * (W_WIDTH / 2) / tan(data->ray->pov / 2);
	top = (W_HEIGHT / 2) - (wall_height / 2);
	bot = (W_HEIGHT / 2) + (wall_height / 2);
	if (bot > W_HEIGHT)
		bot = W_HEIGHT;
	if (top < 0)
		top = 0;
	render_bot_top(data, nmbr_rays, bot, top);
	var.factor = (double)var.texture->height / wall_height;
	var.arr = (int *)var.texture->pixels;
	var.x_offset = get_x_offset(var.texture, data);
	var.y_offset = (top - (W_HEIGHT / 2) + (wall_height / 2)) * var.factor;
	if (var.y_offset < 0)
		var.y_offset = 0;
	while (top < bot)
	{
		if (nmbr_rays >= M_WIDTH || top >= M_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, top, reverse_bytes(var.arr[(int) var.y_offset * var.texture->width + (int)var.x_offset]));
		var.y_offset += var.factor;
		top++;
	}
	
}
