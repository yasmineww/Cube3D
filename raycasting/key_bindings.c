/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:46:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/01 15:04:20 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse(double mouse_x, double mouse_y, void *param)
{
	t_data	*data;
	int		x;
	int		y;

	(void)mouse_x;
	(void)mouse_y;
	data = param;
	mlx_get_mouse_pos(data->mlx->init, &x, &y);
	data->player->view_angle += 0.001 * (double)(x - data->player->x);
	mlx_set_mouse_pos(data->mlx->init, data->player->x, data->player->y);
}

void	key(mlx_key_data_t datakey, void *param)
{
	t_data	*data;
	int		key;
	int		action;

	data = param;
	key = datakey.key;
	action = datakey.action;
	if (key == 256)
	{
		mlx_delete_image(data->mlx->init, data->mlx->img);
		mlx_close_window(data->mlx->init);
		printf("Sad to see you leave :(\n");
		exit(1);
	}
	if (action == 2)
		action = 1;
	if (key == 'W')
		data->player->walk = (action * 1) * 2 * M_PI;
	if (key == 'S')
		data->player->walk = (action * -1) * M_PI;
	if (key == 'D')
		data->player->turn = (action * 1) * (M_PI / 2);
	if (key == 'A')
		data->player->turn = (action * -1) * (M_PI / 2);
	if (key == MLX_KEY_RIGHT)
		data->player->view_angle += (action * 1) * 0.1;
	if (key == MLX_KEY_LEFT)
		data->player->view_angle += (action * -1) * 0.1;
}
