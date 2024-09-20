/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:36 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/09/20 13:32:24 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_put_pixel(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < data->width && y >= 0 && y < data->height)
		mlx_put_pixel(data->mlx->img, x, y, color);
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
				int k = 0;
				while (k < CUBE_SIZE)
				{
					int l = 0;
					while (l < CUBE_SIZE)
					{
						my_put_pixel(data, (l + (j * CUBE_SIZE)), (k + (i * CUBE_SIZE)), 0xFF0000FF);
						l++;
					}
					k++;
				}
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
	data->mlx->img = mlx_new_image(data->mlx->init, data->width, data->height);
	if (!data->mlx->img)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
	render_2d_map(data);
	if (mlx_image_to_window(data->mlx->init, data->mlx->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx->init);
		exit(1);
	}
	// mlx_put_pixel((*data)->mlx->init, 0, 0, 0xFF0000FF);
}

void	init_var(t_data *data, t_list *parsing_lst)
{
	data->height = W_HEIGHT * CUBE_SIZE;
	data->width = W_WIDTH * CUBE_SIZE;
	data->map = parsing_lst->map;
	data->rows = parsing_lst->rows;
	data->cols = parsing_lst->cols;
}

void	data_init(t_data **data, t_list *parsing_lst)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(1);
	(*data)->mlx = malloc (sizeof(t_mlx));
	if (!(*data)->mlx)
		exit(1);
	init_var(*data, parsing_lst);
	(*data)->mlx->init = mlx_init((*data)->width, (*data)->height, "CUBE3D", 0);
	if (!(*data)->mlx->init)
		exit(1);
}
