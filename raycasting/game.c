/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:37:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/21 11:44:20 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_collision(t_data *data, double x, double y)
{
	int	index_x_min;
	int	index_x_max;
	int	index_y_min;
	int	index_y_max;

	index_x_min = (x - data->player->rayon) / CUBE_SIZE;
	index_x_max = (x + data->player->rayon) / CUBE_SIZE;
	index_y_min = (y - data->player->rayon) / CUBE_SIZE;
	index_y_max = (y + data->player->rayon) / CUBE_SIZE;
	if (index_x_min < 0 || index_x_max >= data->cols || index_y_min < 0
		|| index_y_max >= data->rows
		|| data->map[index_y_min][index_x_min] == '1'
		|| data->map[index_y_max][index_x_max] == '1'
		|| data->map[index_y_max][index_x_min] == '1'
		|| data->map[index_y_min][index_x_max] == '1')
		return (1);
	if ((index_x_min < 0 || index_x_max >= data->cols || index_y_min < 0
		|| index_y_max >= data->rows
		|| data->map[index_y_min][index_x_min] == 'D'
		|| data->map[index_y_max][index_x_max] == 'D'
		|| data->map[index_y_max][index_x_min] == 'D'
		|| data->map[index_y_min][index_x_max] == 'D') && data->O_key != 1)
		return (1);
	return (0);
}

void	move_player(t_player *player, t_data *data)
{
	int		x;
	int		y;
	double	angle;

	angle = player->view_angle + player->turn + player->walk;
	x = player->x + player->move_speed * cos(angle);
	y = player->y + player->move_speed * sin(angle);
	if (!wall_collision(data, x, y))
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
		while (j <= size)
		{
			if (j * j + i * i <= size * size)
				mlx_put_pixel(data->mlx->img, (j + M_WIDTH / 2),
					(i + M_HEIGHT / 2), 0x949494FF);
			j++;
		}
		i++;
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
				my_put_pixel(data, (j * CUBE_SIZE + var_x),
					(i * CUBE_SIZE + var_y), 0xFFAA00FF);
			else if (data->map[i][j] == 'D')
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
	create_player(data);
	render_2d_map(data);
	ray_casting(data);
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
}
