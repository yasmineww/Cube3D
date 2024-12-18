/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/29 19:09:46 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_dor_position(t_list *parsing)
{
	t_position_dor	var;
	int				c;
	t_door			*door;

	var.x = 0;
	var.y = 0;
	c = 0;
	while (var.y < parsing->rows)
	{
		while (var.x < parsing->cols)
		{
			if (parsing->map[var.y][var.x] == 'D')
			{
				process_door(parsing, var, &c, &door);
			}
			var.x++;
		}
		var.y++;
		var.x = 0;
	}
	parsing->doors = door;
}

int	the_check(t_list *data, int i, int x)
{
	if (!(
			((data->map[i - 1][x] == '1' && \
			data->map[i + 1][x] == '1') && \
			(data->map[i][x - 1] != '1' && \
			data->map[i][x - 1] != 'D' && \
			data->map[i][x - 1] != '-') && \
			(data->map[i][x + 1] != '1' && \
			data->map[i][x + 1] != 'D' && \
			data->map[i][x + 1] != '-')) || \
			((data->map[i][x - 1] == '1' && \
			data->map[i][x + 1] == '1') && \
			(data->map[i - 1][x] != '1' && \
			data->map[i - 1][x] != 'D' && \
			data->map[i - 1][x] != '-') && \
			(data->map[i + 1][x] != '1' && \
			data->map[i + 1][x] != 'D' && \
			data->map[i + 1][x] != '-'))
		))
		return (1);
	return (0);
}

void	check_curr_door(t_list *data)
{
	int	i;
	int	x;

	i = 0;
	while (i < data->rows)
	{
		x = 0;
		while (x < data->cols)
		{
			if (data->map[i][x] == 'D')
			{
				if (x == data->cols - 1 || i == data->rows - 1)
					print_error(data, "Invalid door position");
				if (the_check(data, i, x) == 1)
					print_error(data, "Invalid door position");
			}
			x++;
		}
		i++;
	}
}

void	parsing(t_list *data, char **argv)
{
	char	*line;
	t_pars	*pars;
	int		num;

	data->texture = NULL;
	data->map = NULL;
	pars = init_parsing(argv, &line, data);
	line = process_parsing(pars, line, data);
	clean_str(pars, data);
	process_pars(data, pars);
	init_texture(data, pars);
	check_texture(data, pars);
	pars = process_map(data, line);
	clean_str(pars, data);
	check_for_tabs(data, pars);
	data->map = get_map(pars, &num, data);
	if (check_map(data) == 1)
		print_error(data, "Invalid Map !\n");
	data->map = create_map(data, data->map, &data->rows, &data->cols);
	get_player_position(data);
	get_dor_position(data);
	check_curr_door(data);
	close(data->fd);
}
