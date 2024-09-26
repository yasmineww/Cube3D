/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/26 11:37:38 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(t_data *data, double x, double y)
{
	int	index_x = x / CUBE_SIZE;
	int	index_y = y / CUBE_SIZE;

	if (index_x < 0 || index_x >= data->cols || index_y < 0 || index_y >= data->rows)
		return (1);
	if (data->map[index_y][index_x] == '1')
		return (1);
	return (0);
}

void	move_player(t_player *player, t_data *data)
{
	int		x;
	int		y;
	double	angle;

	angle = player->rot_angle + player->turn + player->walk;
	x = roundf(player->x + player->move_speed * cos(angle));
	y = roundf(player->y + player->move_speed * sin(angle));
	if (!is_wall(data, x, y))
	{
		if (player->turn || player->walk)
		{
			player->x = x;
			player->y = y;
		}
	}
}

void	draw_pov(t_data *data, t_player *player)
{
	int	i;
	int	j;
	int	ray_x;
	int	ray_y;

	j = -1;
	i = -1;
	while (++j < 20)
	{
		{
			if (player->x < 0 || player->x > W_WIDTH || player->y < 0 || player->y > W_HEIGHT)
				return ;
			ray_x =  player->x + (player->size / 2) + j * cos(player->rot_angle);
			ray_y =  player->y + (player->size / 2) + j * sin(player->rot_angle);
			mlx_put_pixel(data->mlx->img, ray_x, ray_y, 0x94F0ACFF);
		}
		i--;
	}
}

void    create_player(t_data *data)
{
	t_player    *player;
	int         i;
	int         j;

	i = -1;
	player = data->player;
	// draw_pov(data, data->player);
	move_player(data->player, data);
	while (++i < player->size)
	{
		j = -1;
		while (++j < player->size)
		{
			if (player->x >= 0 && player->x < W_WIDTH && player->y >= 0 && player->y < W_HEIGHT)
				mlx_put_pixel(data->mlx->img, (j + player->x),(i + player->y), 0x000000FF);
		}
	}
}

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	int i;
	int	j;
	
	i = -1;
	while (++i < CUBE_SIZE)
	{
		j = -1;
		while (++j < CUBE_SIZE)
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
				my_put_pixel(data, (j * CUBE_SIZE), (i * CUBE_SIZE), 0xFFAA00FF);
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
	ray_casting(data);
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
}
