/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/20 11:42:39 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_window(void *param)
{
	t_data	*data;

	data = param;
	mlx_delete_image(data->mlx->init, data->mlx->img);
	data->mlx->img = mlx_new_image(data->mlx->init, data->width, data->height);
	if (!data->mlx->img)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
	// if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	// {
	// 	mlx_close_window(data->mlx->init);
	// 	puts(mlx_strerror(mlx_errno));
	// 	exit(1);
	// }
	// mlx_put_pixel((*data)->mlx->init, 0, 0, 0xFF0000FF);
}

void	init_var(t_data **data)
{
	(*data)->height = W_HEIGHT * CUBE_SIZE;
	(*data)->width = W_WIDTH * CUBE_SIZE;
}

void	data_init(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(1);
	(*data)->mlx = malloc (sizeof(t_mlx));
	if (!(*data)->mlx)
		exit(1);
	init_var(data);
	(*data)->mlx->init = mlx_init((*data)->width, (*data)->height, "CUBE3D", 0);
	if (!(*data)->mlx->init)
		exit(1);
}
