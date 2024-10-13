/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/13 16:05:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_var(t_data *data, t_list *parsing_lst)
{
	data->map = parsing_lst->map;
	data->rows = parsing_lst->rows;
	data->cols = parsing_lst->cols;
	data->texture = parsing_lst->texture;
	data->scale = 1;
	data->player->x = parsing_lst->x * CUBE_SIZE + CUBE_SIZE / 2;
	data->player->y = parsing_lst->y * CUBE_SIZE + CUBE_SIZE / 2;
	data->player->turn = 0;
	data->player->walk = 0;
	data->player->rayon = 6;
	data->player->view_angle = parsing_lst->view_angle;
	data->player->move_speed = 5;
	data->ray->pov = (60 * M_PI) / 180;
	data->ray->door = 0;
}

void	data_init(t_data **data, t_list *parsing_lst)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(1);
	(*data)->mlx = malloc (sizeof(t_mlx));
	if (!(*data)->mlx)
		exit(1);
	(*data)->player = malloc (sizeof(t_player));
	if (!(*data)->player)
		exit(1);
	(*data)->ray = malloc (sizeof(t_ray));
	if (!(*data)->ray)
		exit(1);
	(*data)->texture = malloc (sizeof(t_texture));
	if (!(*data)->texture)
		exit(1);
	init_var(*data, parsing_lst);
	(*data)->mlx->init = mlx_init(W_WIDTH, W_HEIGHT, "CUBE3D", 0);
	if (!(*data)->mlx->init)
		exit(1);
}
