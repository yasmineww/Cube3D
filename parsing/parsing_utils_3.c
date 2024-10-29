/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:21 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/29 19:08:37 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_and_error(t_list *parsing, t_pars	*temp, char *str)
{
	free_list(parsing, temp);
	print_error(parsing, str);
}

t_process_map	initialize_map_dimensions(t_pars *tmp, t_process_map x, \
					t_list *parsing)
{
	x.rows = 0;
	x.cols = 0;
	x.i = 0;
	x.values = tmp;
	while (tmp)
	{
		if (x.cols < ft_strlen(tmp->value))
			x.cols = ft_strlen(tmp->value);
		x.rows++;
		tmp = tmp->next;
	}
	x.rows += 2;
	x.cols += 2;
	x.arr = (char **)gc_malloc(&parsing->gc, x.rows * sizeof(char *));
	if (x.arr == NULL)
		print_error(parsing, "Allocation Fails for rows!\n");
	while (x.i < x.rows)
	{
		x.arr[x.i] = (char *)gc_malloc(&parsing->gc, x.cols * sizeof(char));
		if (x.arr[x.i] == NULL)
			print_error(parsing, "Allocation Failed for columns!\n");
		x.i++;
	}
	return (x);
}

char	**get_map(t_pars *tmp, int *num, t_list *parsing)
{
	t_process_map	data;

	data.rows = 0;
	data.cols = 0;
	data.i = 0;
	data.values = tmp;
	data = initialize_map_dimensions(tmp, data, parsing);
	if (data.rows <= 4)
		print_error(parsing, "Invalid Map !\n");
	parsing->rows = data.rows;
	parsing->cols = data.cols;
	*num = data.cols;
	fill_map(data.arr, data.cols, data.rows, data.values);
	return (data.arr);
}

void	check_for_tabs(t_list *parsing, t_pars *pars)
{
	int		i;
	t_pars	*temp;

	(void)parsing;
	i = 0;
	temp = pars;
	while (temp)
	{
		while (temp->value[i])
		{
			if (temp->value[i] == '\t')
				print_error(parsing, "Invalid Map : Tabs detected !\n");
			i++;
		}
		temp = temp->next;
		i = 0;
	}
}
