/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 06:06:17 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/29 21:25:02 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	reverse(int c)
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
		x_offeset = (int)fmod(data->ray->distance_v * \
			(ea->width / CUBE_SIZE), ea->width);
	else
		x_offeset = (int)fmod(data->ray->distance_h * \
			(ea->width / CUBE_SIZE), ea->width);
	return (x_offeset);
}

void	render_bottom(t_data *data, int nmbr_rays, double bot)
{
	int	i;

	i = bot;
	while (i < W_HEIGHT)
	{
		if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && bot >= 0 && bot < W_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, i, data->f);
		i++;
	}
}

void	render_top(t_data *data, int nmbr_rays, double top)
{
	int	i;
	int	rand_num;
	int	c;

	i = -1;
	while (++i < top)
	{
		if (nmbr_rays >= M_WIDTH || i >= M_HEIGHT)
		{
			rand_num = rand() % 100;
			c = -1;
			if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && \
				top >= 0 && top < W_HEIGHT)
			{
				if (rand_num == 0)
				{
					while (i++ < top && ++c < 4)
						mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0xFFFF00);
				}
				else
					mlx_put_pixel(data->mlx->img, nmbr_rays, i, data->c);
			}
		}
	}
}

mlx_texture_t	*get_vertical_texture(t_data *data)
{
	if (data->ray->ray_angle > M_PI / 2 && \
		data->ray->ray_angle < 3 * (M_PI / 2))
	{
		if (data->ray->door == 1)
			return (data->mlx->door);
		return (data->mlx->ea);
	}
	else
	{
		if (data->ray->door == 1)
			return (data->mlx->door);
		return (data->mlx->we);
	}
}
