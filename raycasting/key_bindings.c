/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:46:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/13 23:26:10 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse(double mouse_x, double mouse_y, void *param)
{
	t_data	*data;
	t_keys	key;

	(void)mouse_x;
	(void)mouse_y;
	data = param;
	key.window_width = W_HEIGHT;
	key.window_height = W_WIDTH;
	key.center_x = key.window_width / 2;
	key.center_y = key.window_height / 2;
	mlx_get_mouse_pos(data->mlx->init, &key.x, &key.y);
	data->player->view_angle += 0.0009 * (double)(key.x - key.center_x);
	mlx_set_mouse_pos(data->mlx->init, key.center_x, key.center_y);
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
		data->player->view_angle += (action * 1) * 0.05;
	if (key == MLX_KEY_LEFT)
		data->player->view_angle += (action * -1) * 0.05;
}
