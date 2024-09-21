/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:46:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/21 21:45:23 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	key_func(mlx_key_data_t datakey, void *param)
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
	if (key == 'S')
		data->player->walk = (action * 1) * data->player->move_speed;
	if (key == 'W')
		data->player->walk = (action * -1) * data->player->move_speed;
	if (key == 'D')
		data->player->turn = (action * 1) * data->player->move_speed;
	if (key == 'A')
		data->player->turn = (action * -1) * data->player->move_speed;
	if (key == MLX_KEY_RIGHT)
		data->player->rot_angle += (action * 1) * data->player->move_speed * 0.1;
	if (key == MLX_KEY_LEFT)
		data->player->rot_angle += (action * -1) * data->player->move_speed * 0.1;
}
