/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:40:08 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/01 15:17:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render_bot_top(t_data *data, int nmbr_rays, double bot, double top)
{
	int		i;

	i = bot;
	while (i < W_HEIGHT)
	{
		if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && top >= 0 && top < W_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, i, 0XFF0000FF);
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

void	render_wall(t_data *data, double distance, int nmbr_rays)
{
	t_ray	*ray;
	double	wall_height;
	double	top;
	double	bot;

	ray = data->ray;
	wall_height = (CUBE_SIZE / distance) * (W_WIDTH / 2) / tan(ray->pov / 2);
	top = (W_HEIGHT / 2) - (wall_height / 2);
	bot = (W_HEIGHT / 2) + (wall_height / 2);
	if (bot > W_HEIGHT)
		bot = W_HEIGHT;
	if (top < 0)
		top = 0;
    render_bot_top(data, nmbr_rays, bot, top);
	while (top < bot)
	{
		if (nmbr_rays >= 0 && nmbr_rays < W_WIDTH && top >= 0 && top < W_HEIGHT)
			mlx_put_pixel(data->mlx->img, nmbr_rays, top, 0X000000FF);
		top++;
	}
	
}
