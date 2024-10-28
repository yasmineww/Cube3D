/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:43:14 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 22:06:42 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_rest(char *line, t_list *parsing_lst)
{
	while (line != NULL && ft_strcmp(line, "\n") == 0)
	{
		line = get_next_line(parsing_lst->fd, parsing_lst);
		if (line == NULL)
			break ;
		if (skip_line(line) == 0)
			print_error("Invalid Map");
	}
}

t_pars	*process_map(t_list *parsing_lst, char *line)
{
	t_map_handling	v;

	v.temp = gc_malloc(&parsing_lst->gc, sizeof(t_pars));
	if (v.temp == NULL)
		print_error("Allocation Fails !\n");
	v.temp_pars = v.temp;
	if (line == NULL)
		free_and_error(parsing_lst, NULL, "Invalid map !\n");
	while (line && ft_strcmp(line, "\n") != 0 && skip_line(line) == 0)
	{
		v.temp->value = ft_strdup(line, parsing_lst);
		line = get_next_line(parsing_lst->fd, parsing_lst);
		if (line != NULL && ft_strcmp(line, "\n") != 0 && skip_line(line) == 0)
		{
			v.temp->next = gc_malloc(&parsing_lst->gc, sizeof(t_pars));
			if (v.temp->next == NULL)
				print_error("Allocation Fails !\n");
			v.temp = v.temp->next;
			v.temp->next = NULL;
		}
		else
			v.temp->next = NULL;
	}
	check_rest(line, parsing_lst);
	return (v.temp_pars);
}

void	fill_top_border(char **arr, int cols)
{
	int	j;

	j = 0;
	while (j < cols)
	{
		arr[0][j] = '-';
		j++;
	}
}

void	fill_row(char **arr, int cols, int i, t_pars *pars)
{
	int	j;
	int	b;

	j = 0;
	b = 0;
	while (pars->value[b] && j < cols)
	{
		if ((i != 0 && i != cols - 1) && (j == 0 || j == cols - 1))
		{
			arr[i][0] = '-';
			j++;
		}
		else
			arr[i][j++] = pars->value[b++];
	}
	while (j < cols)
	{
		if (j == cols - 1)
			arr[i][j] = '-';
		else
			arr[i][j] = ' ';
		j++;
	}
}

void	fill_map(char **arr, int cols, int rows, t_pars *pars)
{
	int	i;

	fill_top_border(arr, cols);
	i = 1;
	while (pars && i < rows - 1)
	{
		fill_row(arr, cols, i, pars);
		pars = pars->next;
		i++;
	}
	fill_top_border(arr + rows - 1, cols);
}
