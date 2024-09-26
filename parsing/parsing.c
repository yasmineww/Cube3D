/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/24 14:24:59 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*process_line(char *line, int *max_cols, int cols)
{
	t_process_line	arg;

	arg.start = 0;
	arg.end = cols - 1;
	while (line[arg.start] == '-' && arg.start <= arg.end)
		arg.start++;
	while (line[arg.end] == '-' && arg.end >= arg.start)
		arg.end--;
	arg.new_len = arg.end - arg.start + 1;
	if (arg.new_len > *max_cols)
		*max_cols = arg.new_len;
	arg.new_line = (char *)malloc((arg.new_len + 1) * sizeof(char));
	if (!arg.new_line)
		print_error("Allocation fails!\n");
	arg.j = 0;
	while (arg.j < arg.new_len)
	{
		if (line[arg.start + arg.j] == ' ')
			arg.new_line[arg.j] = '-';
		else
			arg.new_line[arg.j] = line[arg.start + arg.j];
		arg.j++;
	}
	arg.new_line[arg.j] = '\0';
	return (arg.new_line);
}

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
	free_pars(pars);
	close(fd);
}
