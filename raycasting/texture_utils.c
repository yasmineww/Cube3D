/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:08:09 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/17 16:08:23 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_data *data)
{
	t_texture	*texture;

	texture = data->texture;
	while (texture)
	{
		if (ft_strcmp(texture->key, "EA") == 0)
			data->mlx->ea = mlx_load_png(texture->value);
		else if (ft_strcmp(texture->key, "NO") == 0)
			data->mlx->no = mlx_load_png(texture->value);
		else if (ft_strcmp(texture->key, "SO") == 0)
			data->mlx->so = mlx_load_png(texture->value);
		else if (ft_strcmp(texture->key, "WE") == 0)
			data->mlx->we = mlx_load_png(texture->value);
		texture = texture->next;
	}
	data->mlx->door = mlx_load_png("textures/door.png");
	if (data->mlx->ea == NULL || data->mlx->no == NULL || \
		data->mlx->so == NULL || data->mlx->we == NULL)
		print_error("Failed to load textures!");
}
