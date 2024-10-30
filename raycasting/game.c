/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/30 01:42:44 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	toggle_door_state(t_door *door)
{
	if (door->is_open == 0)
		door->is_open = 1;
	else if (door->is_open == 1)
		door->is_open = 0;
}

void	render_2d_map(t_data *data)
{
	int		i;
	int		j;
	float	var_x;
	float	var_y;

	move_player(data->player, data);
	var_x = M_WIDTH / 2 - data->player->x;
	var_y = M_HEIGHT / 2 - data->player->y;
	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			if (data->map[i][j] == '1')
				my_put_pixel(data, (j * CUBE_SIZE + var_x),
					(i * CUBE_SIZE + var_y), 0xFFAA00FF);
			else if (data->map[i][j] == 'D')
				my_put_pixel(data, (j * CUBE_SIZE + var_x),
					(i * CUBE_SIZE + var_y), 0xFE641CFF);
			else
				my_put_pixel(data, (j * CUBE_SIZE + var_x),
					(i * CUBE_SIZE + var_y), 0xFFEA7FFF);
		}
	}
}

void	render_window(void *param)
{
	t_data	*data;

	data = param;
	mlx_delete_image(data->mlx->init, data->mlx->img);
	data->mlx->img = mlx_new_image(data->mlx->init, W_WIDTH, W_HEIGHT);
	if (!data->mlx->img)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
	render_2d_map(data);
	create_player(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
}
