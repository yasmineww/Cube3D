/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/19 19:15:46 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_window(void *param)
{
	t_data	*data;

	data = param;
	// data->mlx->init = mlx_init(WIDTH, HEIGHT, "CUB3D", 0);
	// if (!data->mlx->init)
	// {
	// 	printf("%s", mlx_strerror(mlx_errno));
	// 	exit(1);
	// }
	// data->mlx->img = mlx_new_image(data->mlx->init, 128, 128);
	// if (!data->mlx->img)
	// {
	// 	mlx_close_window(data->mlx->init);
	// 	puts(mlx_strerror(mlx_errno));
	// 	exit(1);
	// }
	// if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	// {
	// 	mlx_close_window(data->mlx->init);
	// 	puts(mlx_strerror(mlx_errno));
	// 	exit(1);
	// }
}

void	data_init(t_data **data)
{
	(*data)->mlx = malloc (sizeof(t_mlx));
	if (!(*data)->mlx)
		exit(1);
	(*data)->mlx->init = mlx_init(WIDTH, HEIGHT, "CUBE3D", 0);
	if (!(*data)->mlx->init)
		exit(1);
	(*data)->mlx->img = mlx_new_image((*data)->mlx->init, WIDTH, HEIGHT);
	if (!(*data)->mlx->img || (mlx_image_to_window((*data)->mlx->init, (*data)->mlx->img, 0, 0) < 0))
		exit(1);
	mlx_put_pixel((*data)->mlx->init, 0, 0, 0xFF0000FF);
	mlx_loop_hook((*data)->mlx->init, &render_window, data);
	mlx_loop((*data)->mlx->init);
}
