/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/01 15:00:19 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_is_wall(t_data *data, double x, double y)
{
	int	index_x_min = (x - data->player->rayon) / (CUBE_SIZE * 1);
	int	index_x_max = (x + data->player->rayon) / (CUBE_SIZE * 1);
	int	index_y_min = (y - data->player->rayon) / (CUBE_SIZE * 1);
	int	index_y_max = (y + data->player->rayon) / (CUBE_SIZE * 1);
	
	if (index_x_min < 0 || index_x_max >= data->cols || index_y_min < 0
		|| index_y_max >= data->rows
		|| data->map[index_y_min][index_x_min] == '1'
		|| data->map[index_y_max][index_x_max] == '1'
		|| data->map[index_y_max][index_x_min] == '1'
		|| data->map[index_y_min][index_x_max] == '1')
		return (1);
	return (0);
}

int	is_wall(t_data *data, double x, double y)
{
	int	index_x;
	int	index_y;

	index_x = x / CUBE_SIZE;
	index_y = y / CUBE_SIZE;
	if (index_x < 0 || index_x >= data->cols || index_y < 0
		|| index_y >= data->rows || data->map[index_y][index_x] == '1')
		return (1);
	return (0);
}

void	move_player(t_player *player, t_data *data)
{
	int		x;
	int		y;
	double	angle;
	// int v = 1;
	angle = player->view_angle + player->turn + player->walk;
	x = roundf(player->x + player->move_speed * cos(angle));
	y = roundf(player->y + player->move_speed * sin(angle));
	if (!player_is_wall(data, x, y))
		// v = 0;
	{
		if (player->turn || player->walk)
		{
			player->x = x;
			player->y = y;
		}
	}
}

void	create_player(t_data *data)
{
	t_player	*player;
	// int			i;
	// int			j;

	player = data->player;
	move_player(data->player, data);
	// i = player->rayon * -1;
	// while (i <= player->rayon)
	// {
	// 	j = player->rayon * -1;
	// 	while (j < player->rayon)
	// 	{
	// 		if (j * j + i * i <= player->rayon * player->rayon 
	// 			&& j + player->x < W_WIDTH && i + player->y < W_HEIGHT)
	// 			mlx_put_pixel(data->mlx->img, (j + player->x), (i + player->y),
	// 				0x000000FF);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < CUBE_SIZE * 1)
	{
		j = -1;
		while (++j < CUBE_SIZE * 1)
		{
			if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
				mlx_put_pixel(data->mlx->img, (j + x), (i + y), color);
		}
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
				my_put_pixel(data, (j * CUBE_SIZE* 1), (i * CUBE_SIZE * 1),
					0xFFAA00FF);
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
	// render_2d_map(data);
	create_player(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
}
