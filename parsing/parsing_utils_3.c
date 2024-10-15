/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:21 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/15 19:10:28 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**get_map(t_pars *tmp, int *num, t_list *parsing_lst)
{
	t_process_map	data;

	data.rows = 0;
	data.i = 0;
	data.cols = 0;
	data.values = tmp;
	while (tmp)
	{
		if (data.cols < ft_strlen(tmp->value))
			data.cols = ft_strlen(tmp->value);
		data.rows++;
		tmp = tmp->next;
	}
	data.rows = data.rows + 2;
	data.cols = data.cols + 2;
	data.arr = (char **)malloc(data.rows * sizeof(char *));//protect malloc
	while (data.i < data.rows)
		data.arr[data.i++] = (char *)malloc(data.cols * sizeof(char));//protect malloc
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

	i = 0;
	temp = pars;
	while (temp)
	{
		while (temp->value[i])
		{
			if (temp->value[i] == '\t')
			{
				free_list(parsing_lst, pars);
				print_error("Invalid Map : Tabs detected !\n");
			}
			i++;
		}
		temp = temp->next;
		i = 0;
	}
}
