/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/23 22:44:47 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_animation_frames(t_data *data, t_list *parsing_lst)
{
	char	*filename;
	char	*tmp;
	int		i;

	i = 1;
	data->cross_aim = mlx_load_png("textures/crosshair.png");
	while (i <= 6)
	{
		filename = ft_strjoin("textures/", ft_itoa(i, parsing_lst));
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

void	init_var(t_data *data, t_list *parsing_lst)
{
	data->map = parsing_lst->map;
	data->rows = parsing_lst->rows;
	data->cols = parsing_lst->cols;
	data->texture = parsing_lst->texture;
	data->player->x = parsing_lst->x * CUBE_SIZE + CUBE_SIZE / 2;
	data->player->y = parsing_lst->y * CUBE_SIZE + CUBE_SIZE / 2;
	data->player->turn = 0;
	data->player->walk = 0;
	data->open = 0;
	data->player->rayon = 3;
	data->player->view_angle = parsing_lst->view_angle;
	data->player->move_speed = 7;
	data->ray->pov = (60 * M_PI) / 180;
	data->ray->door = 0;
	data->current_frame = 1;
	data->animation_phase = 1;
}

void	data_init(t_data **data, t_list *parsing_lst)
{
	*data = gc_malloc(&parsing_lst->gc, sizeof(t_data));
	(*data)->mlx = gc_malloc (&parsing_lst->gc, sizeof(t_mlx));
	(*data)->player = gc_malloc (&parsing_lst->gc, sizeof(t_player));
	(*data)->ray = gc_malloc (&parsing_lst->gc, sizeof(t_ray));
	(*data)->texture = gc_malloc (&parsing_lst->gc, sizeof(t_texture));
	(*data)->animation = gc_malloc (&parsing_lst->gc, sizeof(t_animation));
	init_var(*data, parsing_lst);
	(*data)->mlx->init = mlx_init(W_WIDTH, W_HEIGHT, "CUBE3D", 0);
	if (!(*data)->mlx->init)
		exit(1);
	load_textures(*data);
	load_animation_frames(*data, parsing_lst);
}
