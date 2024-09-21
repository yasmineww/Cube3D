/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/21 11:35:13 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_var(t_data *data, t_list *parsing_lst)
{
	// data->height = W_HEIGHT * CUBE_SIZE;
	// data->width = W_WIDTH * CUBE_SIZE;
	data->map = parsing_lst->map;
	data->rows = parsing_lst->rows;
	data->cols = parsing_lst->cols;
	data->player->x = W_WIDTH / 10;
	data->player->y = W_HEIGHT / 10;
	data->player->size = 20;
	data->player->turn = 0;
	data->player->walk = 0;
	data->player->rot_angle = M_PI / 2;
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
	init_var(*data, parsing_lst);
	(*data)->mlx->init = mlx_init(W_WIDTH, W_HEIGHT, "CUBE3D", 0);
	if (!(*data)->mlx->init)
		exit(1);
}
