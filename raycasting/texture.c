/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:47:15 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/13 19:20:17 by ymakhlou         ###   ########.fr       */
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
	while (i <= MAX_FRAMES)
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

	data = (t_data *)param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		data->mouse_clicked = 1;
		if (data->animation_phase == 1)
		{
			data->animation_phase = 2;
			data->current_frame = 2;
			data->animation_direction = 1;
		}
		else
		{
			data->animation_phase = 1;
			data->current_frame = 1;
			data->animation_direction = 1;
		}
	}
}

void	handle_animation_phase(t_data *data)
{
	if (data->animation_phase == 1)
	{
		data->current_frame += data->animation_direction;
		if (data->current_frame >= 1)
		{
			data->current_frame = 2;
			data->animation_direction = -1;
		}
		else if (data->current_frame <= 1)
		{
			data->current_frame = 1;
			data->animation_direction = 1;
		}
	}
	else if (data->animation_phase == 2)
	{
		data->current_frame++;
		if (data->current_frame > 8)
		{
			data->current_frame = 7;
			data->animation_phase = 1;
		}
	}
	if (data->current_frame > MAX_FRAMES)
		data->current_frame = 1;
}

void	handle_mouse_click(t_data *data)
{
	if (data->mouse_clicked)
	{
		data->current_frame = 1;
		data->animation_phase = 2;
		data->mouse_clicked = 0;
	}
}

void increment_frame_delay_counter(t_data *data)
{
	data->frame_delay_counter++;
	if (data->frame_delay_counter >= data->frame_delay)
		data->frame_delay_counter = 0;
}

void	manage_animation_frame(t_data *data)
{
	increment_frame_delay_counter(data);//name shouldnt have more than 3 words
	if (data->frame_delay_counter == 0)
	{
		handle_mouse_click(data);
		handle_animation_phase(data);
	}
}

void	process_pixel_data(t_animation *var, int x_offset, int y_offset, float scale_factor, t_data *data)
{
	int	dy;
	int	dx;
	int	scaled_x;
	int	scaled_y;

	if (var->a != 0)
	{
		var->target_x = x_offset + (var->x * scale_factor);
		var->target_y = y_offset + (var->y * scale_factor);
		dy = 0;
		while (dy < scale_factor)
		{
			dx = 0;
			while (dx < scale_factor)
			{
				scaled_x = var->target_x + dx;
				scaled_y = var->target_y + dy;
				if (scaled_x >= 0 && scaled_x < W_WIDTH && scaled_y >= 0 \
					&& scaled_y < W_HEIGHT)
				{
					var->color = (var->a << 24) | \
					(var->b_color << 16) | (var->g << 8) | var->r;
					var->color = reverse_bytes(var->color);
					mlx_put_pixel(data->mlx->img, \
						scaled_x, scaled_y, var->color);
				}
				dx++;
			}
			dy++;
		}
	}
}

void	draw_scaled_pixels(t_animation var, t_data *data, float scale_factor)
{
	int	x_offset;
	int	y_offset;

	x_offset = 150;
	y_offset = 210;
	while (var.y < var.texture->height)
	{
		var.x = 0;
		while (var.x < var.texture->width)
		{
			var.pixel_index = (var.y * var.texture->width + var.x) * 4;
			var.r = var.texture->pixels[var.pixel_index + 0];
			var.g = var.texture->pixels[var.pixel_index + 1];
			var.b_color = var.texture->pixels[var.pixel_index + 2];
			var.a = var.texture->pixels[var.pixel_index + 3];
			process_pixel_data(&var, x_offset, y_offset, scale_factor, data);
			var.x++;
		}
		var.y++;
	}
}

t_animation	prepare_texture(t_data *data)
{
	t_animation	var;

	var.x = 0;
	var.y = 0;
	if (data->current_frame > MAX_FRAMES)
		data->current_frame = 1;
	if (!data->images[data->current_frame - 1])
		return (var);
	var.texture = data->images[data->current_frame - 1];
	if (!var.texture || !data->mlx->img)
		return (var);
	return (var);
}

void	draw_texture_with_put_pixel(t_data *data, float scale_factor)
{
	t_animation	var;
	int			x_offset;
	int			y_offset;

	x_offset = 150;
	y_offset = 210;
	var = prepare_texture(data);
	if (!var.texture || !data->mlx->img)
		return ;
	draw_scaled_pixels(var, data, scale_factor);
	manage_animation_frame(data);
}
