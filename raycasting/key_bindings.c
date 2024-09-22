/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:46:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/22 14:30:53 by ymakhlou         ###   ########.fr       */
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
		data->player->walk = (action * 1);
	if (key == 'W')
		data->player->walk = (action * -1);
	if (key == 'D')
		data->player->turn = (action * 1);
	if (key == 'A')
		data->player->turn = (action * -1);
	if (key == MLX_KEY_RIGHT)
		data->player->rot_angle += (action * 1) * 0.3;
	if (key == MLX_KEY_LEFT)
		data->player->rot_angle += (action * -1) * 0.3;
}
