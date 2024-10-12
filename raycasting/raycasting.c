/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:53:56 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/10 13:42:39 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	draw_ray(t_data *data, double distance)
// {
// 	int	ray_x;
// 	int	ray_y;

// 	while (--distance >= 0)
// 	{
// 		{
// 			if (data->player->x < 0 || data->player->x > W_WIDTH || data->player->y < 0 || data->player->y > W_HEIGHT)
// 				return ;
// 			ray_x = (data->player->x + cos(data->ray->ray_angle) * distance) * 1;
// 			ray_y = (data->player->y + sin(data->ray->ray_angle) * distance) * 1;
// 			mlx_put_pixel(data->mlx->img, ray_x,  ray_y, 0x94C8F0FF);
// 		}
// 	}
// }

float	normalize(float angle, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 0 && angle < M_PI)
		ray->down = 1;
	if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
		ray->left = 1;
	ray->up = !ray->down;
	ray->right = !ray->left;
	return (angle);
}

double	h_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;

	ystep = CUBE_SIZE;
	if (data->ray->up)
		ystep *= -1;
	xstep = fabs(CUBE_SIZE / tan(data->ray->ray_angle));
	if (data->ray->left)
		xstep *= -1;
	pos_y = (data->player->y / CUBE_SIZE + ray->down) * CUBE_SIZE;
	pos_x = data->player->x + (pos_y - data->player->y) / tan(ray->ray_angle);
	while (!is_wall(data, pos_x, pos_y - data->ray->up))
	{
		pos_x += xstep;
		pos_y += ystep;
	}
	ray->distance_h = pos_x;
	return (hypot(pos_x - data->player->x, pos_y - data->player->y));
}

double	v_intersect(t_data *data, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	pos_x;
	double	pos_y;

	xstep = CUBE_SIZE;
	if (data->ray->left)
		xstep *= -1;
	ystep = fabs(CUBE_SIZE * tan(data->ray->ray_angle));
	if (data->ray->up)
		ystep *= -1;
	pos_x = (data->player->x / CUBE_SIZE + ray->right) * CUBE_SIZE;
	pos_y = data->player->y + (pos_x - data->player->x) * tan(ray->ray_angle);
	while (!is_wall(data, pos_x - data->ray->left, pos_y))
	{
		pos_x += xstep;
		pos_y += ystep;
	}
	ray->distance_v = pos_y;
	return (hypot(pos_x - data->player->x, pos_y - data->player->y));
}

void	cast_one_ray(t_data *data, int nmbr_rays)
{
	t_ray	*ray;
	double	distance_h;
	double	distance_v;
	double	distance;

	data->ray->door = 0;
	ray = data->ray;
	ray->ray_angle = normalize(ray->ray_angle, ray);
	distance_h = h_intersect(data, ray);
	distance_v = v_intersect(data, ray);
	distance = distance_h;
	ray->is_v = 0;
	if (distance_h > distance_v)
		{
			distance = distance_v;
			ray->is_v = 1;
		}
	distance *= cos(ray->ray_angle - data->player->view_angle);//fish eye
	// draw_ray(data, distance);
	render_wall(data, distance, nmbr_rays);
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
	int			x_offset;
	int			y_offset;

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

void increment_frame_delay_counter(t_data *data)
{
	data->frame_delay_counter++;
	if (data->frame_delay_counter >= data->frame_delay)
		data->frame_delay_counter = 0;
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

void	manage_animation_frame(t_data *data)
{
	increment_frame_delay_counter(data);
	if (data->frame_delay_counter == 0)
	{
		handle_mouse_click(data);
		handle_animation_phase(data);
	}
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

t_walls_texture	*load_textures(t_texture *texture)
{
	t_walls_texture	*var;
	t_texture		*tmp;

	var = malloc(sizeof(t_walls_texture));
	tmp = texture;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "EA") == 0)
			var->ea = mlx_load_png(tmp->value);
		else if (ft_strcmp(tmp->key, "NO") == 0)
			var->no = mlx_load_png(tmp->value);
		else if (ft_strcmp(tmp->key, "SO") == 0)
			var->so = mlx_load_png(tmp->value);
		else if (ft_strcmp(tmp->key, "WE") == 0)
			var->we = mlx_load_png(tmp->value);
		tmp = tmp->next;
	}
	var->door = mlx_load_png("textures/door.png");
	var->img = mlx_load_png("textures/1.png");
	if (var->ea == NULL || var->no == NULL || \
		var->so == NULL || var->we == NULL)
		print_error("Failed to load textures!");
	return (var);
}

void	ray_casting(t_data *data)
{
	t_ray			*ray;
	int				nmbr_rays;
	t_walls_texture	*textures;

	nmbr_rays = 0;
	ray = data->ray;
	ray->ray_angle = data->player->view_angle - (ray->pov / 2);
	textures = load_textures(data->texture);
	data->open_textures = textures;
	while (nmbr_rays < W_WIDTH)
	{
		cast_one_ray(data, nmbr_rays);
		ray->ray_angle += (ray->pov / W_WIDTH);
		nmbr_rays++;
	}
	draw_texture_with_put_pixel(data, 2);
}
