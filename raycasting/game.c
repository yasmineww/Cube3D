/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/21 20:50:29 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_player *player)
{
	if (player->x + player->turn < W_WIDTH && player->y + player->walk < W_HEIGHT
		&& player->x + player->turn >= 0 && player->y + player->walk >= 0)
	{
			player->x += player->turn;
			player->y += player->walk;
			// player->rot_angle += player->move_speed + player->turn;
	}
}

void	draw_ray(t_data *data, t_player *player)
{
	int	i;
	int	j;
	int	pos_x;
	int	pos_y;

	j = 0;
	i = -1;
	while (j < 20)
	{
		{
			if (player->x >= 0 && player->x < W_WIDTH && player->y >= 0 && player->y < W_HEIGHT)
			{
				pos_x = player->x + (player->size / 2) + cos(player->rot_angle);
				pos_y = i + player->y + sin(player->rot_angle);
				mlx_put_pixel(data->mlx->img, pos_x, pos_y, 0x94F0ACFF);
				// mlx_put_pixel(data->mlx->img, ((player->x + (player->size / 2)) + cos(player->rot_angle)),
				// 		(( i + player->y) + sin(player->rot_angle)), 0x94F0ACFF);
			}
			
		}
		j++;
		i--;
	}
}

void    create_player(t_data *data)
{
	t_player    *player;
	int         i;
	int         j;

	i = 0;
	player = data->player;
	move_player(data->player);
	while (i < player->size)
	{
		j = 0;
		while (j < player->size)
		{
			if (player->x >= 0 && player->x < W_WIDTH && player->y >= 0 && player->y < W_HEIGHT)
			{
				mlx_put_pixel(data->mlx->img, (j + player->x),(i + player->y), 0x000000FF);
			}
			j++;
		}
		i++;
	}
	draw_ray(data, data->player);
}

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	int i;
	int	j;
	
	i = 0;
	while (i < CUBE_SIZE)
	{
		j = 0;
		while (j < CUBE_SIZE)
		{
			if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
				mlx_put_pixel(data->mlx->img, (j + x), (i + y), color);
			j++;
		}
		i++;
	}
}

void	render_2d_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			if (data->map[i][j] == '1')
			{
				my_put_pixel(data, (j * CUBE_SIZE), (i * CUBE_SIZE), 0xFF0000FF);
			}
			j++;
		}
		i++;
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
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
}
