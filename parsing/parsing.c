/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/15 04:18:03 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_map(char **map, int *old_rows, int *cols)
{
	t_map_create	arg;

	arg.max = 0;
	arg.new_rows = (*old_rows) - 2;
	arg.new_map = (char **)malloc(arg.new_rows * sizeof(char *));
	if (!arg.new_map)
		print_error("Allocation Fails !\n");
	arg.i = 1;
	arg.row_index = 0;
	while (arg.i < *old_rows - 1)
	{
		arg.new_map[arg.row_index] = process_line(map[arg.i], &arg.max, *cols);
		arg.row_index++;
		arg.i++;
	}
	arg.i = 0;
	while (arg.i < *old_rows)
	{
		free(map[arg.i]);
		arg.i++;
	}
	free(map);
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
				parsing->x = x;
				parsing->y = y;
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

void	parsing(t_list *parsing, char **argv)
{
	int		fd;
	char	*line;
	t_pars	*pars;
	int		num;

	parsing->texture = NULL;
	parsing->map = NULL;
	pars = init_parsing(argv, &fd, &line);
	line = process_parsing(pars, fd, line);
	clean_str(pars);
	process_pars(parsing, pars);
	init_texture(parsing, pars);
	check_texture(parsing, pars);
	free_pars(pars);
	pars = process_map(parsing, fd, line);
	clean_str(pars);
	check_for_tabs(parsing, pars);
	parsing->map = get_map(pars, &num, parsing);
	if (check_map(parsing) == 1)
		print_error("Invalid Map !\n");
	parsing->map = create_map(parsing->map, &parsing->rows, &parsing->cols);
	get_player_position(parsing);
	get_dor_position(parsing);
	free_pars(pars);
	close(fd);
}
