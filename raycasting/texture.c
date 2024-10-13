/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:47:15 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/14 00:34:08 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_data *data)
{
	t_texture	*texture;

	texture = data->texture;
	while (texture)
	{
		if (ft_strcmp(texture->key, "EA") == 0)
			data->mlx->ea = mlx_load_png(texture->value);
		else if (ft_strcmp(texture->key, "NO") == 0)
			data->mlx->no = mlx_load_png(texture->value);
		else if (ft_strcmp(texture->key, "SO") == 0)
			data->mlx->so = mlx_load_png(texture->value);
		else if (ft_strcmp(texture->key, "WE") == 0)
			data->mlx->we = mlx_load_png(texture->value);
		texture = texture->next;
	}
	data->mlx->door = mlx_load_png("textures/door.png");
	if (data->mlx->ea == NULL || data->mlx->no == NULL || \
		data->mlx->so == NULL || data->mlx->we == NULL)
		print_error("Failed to load textures!");
}

void	load_animation_frames(t_data *data)
{
	char	*filename;
	char	*tmp;
	int		i;

	i = 1;
	while (i <= 6)
	{
		filename = ft_strjoin("textures/", ft_itoa(i));
		tmp = filename;
		filename = ft_strjoin(tmp, ".png");
		free(tmp);
		data->images[i - 1] = mlx_load_png(filename);
		free(filename);
		if (!data->images[i - 1])
			print_error("Failed to load image \n");
		i++;
	}
}

void	mouse_click_handler(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_data	*data;

	data = param;
	(void)mods;
	data->mouse_clicked = 0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		data->mouse_clicked = 1;
		if (data->animation_phase == 1)
		{
			data->animation_phase = 2;
			data->current_frame = 2;
		}
		else
		{
			data->animation_phase = 1;
			data->current_frame = 1;
		}
	}
}

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

void	process_pixel_data(t_animation *animation, t_data *data)
{
	int	dy;
	int	dx;
	int	scaled_x;
	int	scaled_y;

	if (animation->a != 0)
	{
		dy = -1;
		while (++dy < 3)
		{
			dx = -1;
			while (++dx < 3)
			{
				scaled_x = 700 + (animation->x * 3) + dx;
				scaled_y = 680 + (animation->y * 3) + dy;
				if (scaled_x >= 0 && scaled_x < W_WIDTH && scaled_y >= 0 \
					&& scaled_y < W_HEIGHT)
				{
					animation->color = (animation->a << 24) | \
					(animation->b << 16) | (animation->g << 8) | animation->r;
					animation->color = reverse_bytes(animation->color);
					mlx_put_pixel(data->mlx->img, \
						scaled_x, scaled_y, animation->color);
				}
			}
		}
	}
}

void	draw_sprite(t_data *data)
{
	t_animation	*animation;

	animation = data->animation;
	data->animation->frame = data->images[data->current_frame - 1];
	animation->y = -1;
	while (++animation->y < animation->frame->height)
	{
		animation->x = -1;
		while (++animation->x < animation->frame->width)
		{
			animation->pixel_index = (animation->y * animation->frame->width + animation->x) * 4;
			animation->r = animation->frame->pixels[animation->pixel_index + 0];
			animation->g = animation->frame->pixels[animation->pixel_index + 1];
			animation->b = animation->frame->pixels[animation->pixel_index + 2];
			animation->a = animation->frame->pixels[animation->pixel_index + 3];
			process_pixel_data(animation, data);
		}
	}
	manage_animation_frame(data);
}
