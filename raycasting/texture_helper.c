/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:49:28 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/21 16:50:02 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	process_cross_aim(t_data *data, t_animation *animation, int flag)
{
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
}

void	draw_sprite(t_data *data)
{
	t_animation	*animation;
	int			flag;

	flag = 0;
	animation = data->animation;
	data->animation->frame = data->images[data->current_frame - 1];
	process_sprite_frame(data, animation, flag);
	process_cross_aim(data, animation, flag);
	manage_animation_frame(data);
}
