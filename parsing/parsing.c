/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/27 20:45:50 by youbihi          ###   ########.fr       */
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

void	parsing(t_list *data, char **argv)
{
	int		fd;
	char	*line;
	t_pars	*pars;
	int		num;

	data->texture = NULL;
	data->map = NULL;
	pars = init_parsing(argv, &fd, &line, data);
	line = process_parsing(pars, fd, line, data);
	clean_str(pars, data);
	process_pars(data, pars);
	init_texture(data, pars);
	check_texture(data, pars);
	pars = process_map(data, fd, line);
	clean_str(pars, data);
	check_for_tabs(data, pars);
	data->map = get_map(pars, &num, data);
	if (check_map(data) == 1)
		print_error("Invalid Map !\n");
	data->map = create_map(data, data->map, &data->rows, &data->cols);
	get_player_position(data);
	get_dor_position(data);
	close(fd);
}
