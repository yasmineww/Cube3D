/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:46:37 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/27 21:01:42 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_click_handler(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param)
{
	t_data	*data;

	data = param;
	(void)mods;
	data->mouse_clicked = 0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		data->mouse_clicked = 1;
		if (data->animation_phase == 1)
		{
			data->animation_phase = 2;
			data->current_frame = 2;
		}
		else
		{
			data->animation_phase = 1;
			data->current_frame = 1;
		}
	}
}

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

void	open_key(t_data *data, int key, int action)
{
	t_door	*door;

	if (key == 'O' && action == 1)
	{
		door = data->doors;
		while (door)
		{
			if ((((data->player->x / CUBE_SIZE) == door->x + 1) && \
				(data->player->y / CUBE_SIZE) == door->y) || \
				(((data->player->x / CUBE_SIZE) == door->x - 1) && \
				(data->player->y / CUBE_SIZE) == door->y) || \
				(((data->player->x / CUBE_SIZE) == door->x) && \
				(data->player->y / CUBE_SIZE) == door->y + 1) || \
				(((data->player->x / CUBE_SIZE) == door->x) && \
				(data->player->y / CUBE_SIZE) == door->y - 1))
			{
				toggle_door_state(door);
			}
			door = door->next;
		}
	}
}

void	esc_key(t_data *data, int key)
{
	if (key == 256)
	{
		mlx_delete_image(data->mlx->init, data->mlx->img);
		mlx_close_window(data->mlx->init);
		printf("Sad to see you leave :(\n");
		exit(1);
	}
}

void	key(mlx_key_data_t datakey, void *param)
{
	t_data	*data;
	int		key;
	int		action;
	t_door	*door;

	data = param;
	door = data->doors;
	key = datakey.key;
	action = datakey.action;
	esc_key(data, key);
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
	open_key(data, key, action);
}
