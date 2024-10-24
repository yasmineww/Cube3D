/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/24 09:04:16 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_map(t_list *parsing, char **map, int *old_rows, int *cols)
{
	t_map_create	arg;

	arg.max = 0;
	arg.new_rows = (*old_rows) - 2;
	arg.new_map = (char **)gc_malloc(&parsing->gc, \
		arg.new_rows * sizeof(char *));
	if (!arg.new_map)
		print_error("Allocation Fails !\n");
	arg.i = 1;
	arg.row_index = 0;
	while (arg.i < *old_rows - 1)
	{
		arg.new_map[arg.row_index] = process_line(parsing, \
			map[arg.i], &arg.max, *cols);
		arg.row_index++;
		arg.i++;
	}
	arg.i = 0;
	*old_rows = arg.new_rows;
	*cols = arg.max;
	return (arg.new_map);
}

int	check_curr_char(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

void	get_player_position(t_list *parsing)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < parsing->rows)
	{
		while (y < parsing->cols)
		{
			if (check_curr_char(parsing->map[x][y]) == 1)
			{
				parsing->x = y;
				parsing->y = x;
			}
			y++;
		}
		x++;
		y = 0;
	}
}

void	get_dor_position(t_list *parsing)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < parsing->rows)
	{
		while (y < parsing->cols)
		{
			if (parsing->map[x][y] == 'D')
			{
				if ((parsing->map[x - 1][y] != '1' && \
					parsing->map[x + 1][y] != '1') && \
					(parsing->map[x][y + 1] != '1' && \
					parsing->map[x][y + 1] != '1'))
					print_error("Invalid Dor position !\n");
			}
			y++;
		}
		x++;
		y = 0;
	}
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
