/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:47:15 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/21 10:32:49 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	manage_animation_frame(t_data *data)
{
	if (data->animation_phase == 1)
		data->current_frame = 1;
	else if (data->animation_phase == 2)
	{
		data->current_frame++;
		if (data->current_frame > 6)
		{
			data->current_frame = 1;
			data->animation_phase = 1;
		}
	}
}

void	process_pixel_data(t_animation *animation, t_data *data, int flag)
{
	t_pixel_data	var;
	int				x;
	int				y;
	int				c;

	if (flag == 0)
	{
		x = 800;
		y = 680;
		c = 3;
	}
	else
	{
		x = 700;
		y = 500;
		c = 2;
	}
	if (animation->a != 0)
	{
		var.dy = -1;
		while (++var.dy < 3)
		{
			var.dx = -1;
			while (++var.dx < 3)
			{
				var.scaled_x = x + (animation->x * c) + var.dx;
				var.scaled_y = y + (animation->y * c) + var.dy;
				if (var.scaled_x >= 0 && var.scaled_x < W_WIDTH \
					&& var.scaled_y >= 0 \
					&& var.scaled_y < W_HEIGHT)
				{
					animation->color = (animation->a << 24) | \
					(animation->b << 16) | (animation->g << 8) | animation->r;
					animation->color = reverse_bytes(animation->color);
					mlx_put_pixel(data->mlx->img, \
						var.scaled_x, var.scaled_y, animation->color);
				}
			}
		}
	}
}

void	draw_sprite(t_data *data)
{
	t_animation	*animation;
	int			flag;

	flag = 0;
	animation = data->animation;
	data->animation->frame = data->images[data->current_frame - 1];
	animation->y = -1;
	while (++animation->y < animation->frame->height)
	{
		animation->x = -1;
		while (++animation->x < animation->frame->width)
		{
			animation->pixel_index = (animation->y * \
				animation->frame->width + animation->x) * 4;
			animation->r = animation->frame->pixels[animation->pixel_index + 0];
			animation->g = animation->frame->pixels[animation->pixel_index + 1];
			animation->b = animation->frame->pixels[animation->pixel_index + 2];
			animation->a = animation->frame->pixels[animation->pixel_index + 3];
			process_pixel_data(animation, data, flag);
		}
	}
	animation->y = -1;
	while (++animation->y < data->cross_aim->height)
	{
		flag = 1;
		animation->x = -1;
		while (++animation->x < data->cross_aim->width)
		{
			animation->pixel_index = (animation->y * \
				data->cross_aim->width + animation->x) * 4;
			animation->r = data->cross_aim->pixels[animation->pixel_index + 0];
			animation->g = data->cross_aim->pixels[animation->pixel_index + 1];
			animation->b = data->cross_aim->pixels[animation->pixel_index + 2];
			animation->a = data->cross_aim->pixels[animation->pixel_index + 3];
			process_pixel_data(animation, data, flag);
		}
	}
	manage_animation_frame(data);
}
