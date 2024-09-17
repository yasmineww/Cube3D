/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:21 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/17 08:54:55 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_and_error(t_list *parsing_lst, t_pars	*temp, char *str)
{
	free_list(parsing_lst, temp);
	print_error(str);
}

t_pars	*process_map(t_list *parsing_lst, int fd, char *line)
{
	t_pars	*temp_pars;
	t_pars	*temp;
	int		i;

	temp = malloc(sizeof(t_pars));
	temp_pars = temp;
	i = 0;
	if (line == NULL)
		free_and_error(parsing_lst, NULL, "Invalid map !\n");
	while (line && ft_strcmp(line, "\n") != 0 && skip_line(line) == 0)
	{
		temp->value = ft_strdup(line);
		line = get_next_line(fd);
		if (line != NULL && ft_strcmp(line, "\n") != 0 && skip_line(line) == 0)
		{
			temp->next = malloc(sizeof(t_pars));
			temp = temp->next;
			temp->next = NULL;
		}
		else
			temp->next = NULL;
	}
	return (temp_pars);
}

void	fill_map(char **arr, int cols, int rows, t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (pars->value[j] && j < cols)
		{
			arr[i][j] = pars->value[j];
			j++;
		}
		while (j < cols)
		{
			arr[i][j] = ' ';
			j++;
		}
		pars = pars->next;
		i++;
	}
}

char	**get_map(t_pars *tmp, int *num)
{
	size_t		rows;
	size_t		cols;
	char		**arr;
	size_t		i;
	t_pars		*values;

	rows = 0;
	i = 0;
	cols = 0;
	values = tmp;
	while (tmp)
	{
		if (cols < ft_strlen(tmp->value))
			cols = ft_strlen(tmp->value);
		rows++;
		tmp = tmp->next;
	}
	arr = (char **)malloc(rows * sizeof(char *));
	while (i < rows)
	{
		arr[i++] = (char *)malloc(cols * sizeof(char));
	}
	*num = cols;
	fill_map(arr, cols, rows, values);
	return (arr);
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
