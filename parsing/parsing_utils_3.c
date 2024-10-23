/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:21 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/22 14:09:42 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_process_map	initialize_map_dimensions(t_pars *tmp, t_process_map data, \
					t_list *parsing_lst)
{
	data.rows = 0;
	data.cols = 0;
	data.i = 0;
	data.values = tmp;
	while (tmp)
	{
		if (data.cols < ft_strlen(tmp->value))
			data.cols = ft_strlen(tmp->value);
		data.rows++;
		tmp = tmp->next;
	}
	data.rows += 2;
	data.cols += 2;
	data.arr = (char **)gc_malloc(&parsing_lst->gc, data.rows * sizeof(char *));
	if (data.arr == NULL)
		print_error("Allocation Fails for rows!\n");
	while (data.i < data.rows)
	{
		data.arr[data.i] = (char *)gc_malloc(&parsing_lst->gc, data.cols * sizeof(char));
		if (data.arr[data.i] == NULL)
			print_error("Allocation Failed for columns!\n");
		data.i++;
	}
	return (data);
}

char	**get_map(t_pars *tmp, int *num, t_list *parsing_lst)
{
	t_process_map	data;

	data.rows = 0;
	data.cols = 0;
	data.i = 0;
	data.values = tmp;
	data = initialize_map_dimensions(tmp, data, parsing_lst);
	if (data.rows <= 4)
		print_error("Invalid Map !\n");
	parsing_lst->rows = data.rows;
	parsing_lst->cols = data.cols;
	*num = data.cols;
	fill_map(data.arr, data.cols, data.rows, data.values);
	return (data.arr);
}

void	check_for_tabs(t_list *parsing_lst, t_pars *pars)
{
	int		i;
	t_pars	*temp;

	(void)parsing_lst;
	i = 0;
	temp = pars;
	while (temp)
	{
		while (temp->value[i])
		{
			if (temp->value[i] == '\t')
				print_error("Invalid Map : Tabs detected !\n");
			i++;
		}
		temp = temp->next;
		i = 0;
	}
}
