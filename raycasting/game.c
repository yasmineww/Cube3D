/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/23 12:13:53 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_data *data, double x, double y)
{
	int	index_x = x / CUBE_SIZE;
	int	index_y = y / CUBE_SIZE;

	if (x < 0 || x > W_WIDTH || y < 0 || y > W_HEIGHT)
		return (1);
	if (data->map[index_y][index_x] == '1')
		return (1);
	return (0);
}

void	move_player(t_player *player, t_data *data)
{
	double	var_1;
	double	var_2;
	double	angle;

	var_1 = player->x;
	var_2 = player->y;
	angle = player->rot_angle + player->turn + player->walk;
	var_1 = roundf(player->x + player->move_speed * cos(angle));
	var_2 = roundf(player->y + player->move_speed * sin(angle));
	if (var_1 < W_WIDTH && var_2 < W_HEIGHT
		&& var_1 >= 0 && var_2 >= 0)
	{
		var_1 = roundf(player->x + player->move_speed * cos(angle));
		var_2 = roundf(player->y + player->move_speed * sin(angle));
		if (!is_wall(data, var_1, var_2))
		{
			if (player->turn || player->walk)
			{
				player->x = roundf(player->x + player->move_speed * cos(angle));
				player->y = roundf(player->y + player->move_speed * sin(angle));
			}
		}
	}
}

void	draw_ray(t_data *data, t_player *player)
{
	int	i;
	int	j;
	int	ray_x;
	int	ray_y;

	j = 0;
	i = -1;
	while (j < 20)
	{
		{
			if (player->x >= 0 && player->x < W_WIDTH && player->y >= 0 && player->y < W_HEIGHT)
			{
				ray_x =  player->x + (player->size / 2) + j * cos(player->rot_angle);
				ray_y =  player->y + (player->size / 2) + j * sin(player->rot_angle);
				mlx_put_pixel(data->mlx->img, ray_x, ray_y, 0x94F0ACFF);
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
	move_player(data->player, data);
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
