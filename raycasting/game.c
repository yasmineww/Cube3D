/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/13 23:31:35 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_is_wall(t_data *data, double x, double y)
{
	int	index_x_min = (x - data->player->rayon) / CUBE_SIZE;
	int	index_x_max = (x + data->player->rayon) / CUBE_SIZE;
	int	index_y_min = (y - data->player->rayon) / CUBE_SIZE;
	int	index_y_max = (y + data->player->rayon) / CUBE_SIZE;
	
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
	else if (index_x < 0 || index_x >= data->cols || index_y < 0
		|| index_y >= data->rows || data->map[index_y][index_x] == 'D')
		{
			if ((data->player->x >= x - 50 && data->player->y >= y + 50)
			|| (data->player->x >= x + 50 && data->player->y >= y - 50)
			|| (data->player->x <= x - 50 && data->player->y <= y + 50)
			|| (data->player->x <= x + 50 && data->player->y <= y - 50))
			{
				data->ray->door = 1;
				return (1);
			}
		}
	return (0);
}

void	move_player(t_player *player, t_data *data)
{
	int		x;
	int		y;
	double	angle;

	angle = player->view_angle + player->turn + player->walk;
	x = roundf(player->x + player->move_speed * cos(angle));
	y = roundf(player->y + player->move_speed * sin(angle));
	if (!player_is_wall(data, x, y))
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
	int			size;
	int			i;
	int			j;

	size = 7;
	player = data->player;
	move_player(data->player, data);
	i = size * -1;
	while (i <= size)
	{
		j = size * -1;
		while (j < size)
		{
			if (j * j + i * i <= size * size && j + player->x < W_WIDTH
				&& i + player->y < W_HEIGHT)
				mlx_put_pixel(data->mlx->img, (j + M_WIDTH / 2), (i + M_HEIGHT / 2),
					0x949494FF);
			j++;
		}
		i++;
	}
}

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < CUBE_SIZE)
	{
		j = -1;
		while (++j < CUBE_SIZE)
		{
			if ((j + x) >= 0 && (i + y) >= 0 && (j + x) < M_WIDTH && (i + y) < M_HEIGHT)
				mlx_put_pixel(data->mlx->img, (j + x), (i + y), color);
		}
	}
}

void	render_2d_map(t_data *data)
{
	int		i;
	int		j;
	float	var_x;
	float	var_y;

	var_x = M_WIDTH / 2 - data->player->x;
	var_y = M_HEIGHT / 2 - data->player->y;
	i = -1;
	while (++i < data->rows)
	{
		j = -1;
		while (++j < data->cols)
		{
			if (data->map[i][j] == '1')
				my_put_pixel(data, (j * CUBE_SIZE + var_x), (i * CUBE_SIZE + var_y),
					0xFFAA00FF);
			else if (data->map[i][j] == 'D')
				my_put_pixel(data, (j * CUBE_SIZE + var_x), (i * CUBE_SIZE + var_y),
					0xFFEA7FFF);
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
	create_player(data);
	render_2d_map(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
}
