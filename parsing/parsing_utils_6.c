/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:50:01 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 22:26:23 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_door(t_list *parsing, int x, int y)
{
	if ((parsing->map[y - 1][x] == 'D' || \
		parsing->map[y + 1][x] == 'D') || \
		(parsing->map[y][x + 1] == 'D' || \
		parsing->map[y][x + 1] == 'D'))
		print_error(parsing, "Invalid Door position !\n");
}

void	clean_str(t_pars *pars, t_list *parsing)
{
	t_pars		*temp;
	char		*str;

	temp = pars;
	while (temp)
	{
		str = ft_custom_strdup(temp->value, parsing);
		temp->value = str;
		temp = temp->next;
	}
}

int	check_unwanted_characters(t_list *parsing)
{
	int	i;
	int	j;
	int	h;

	i = 1;
	j = 1;
	h = 0;
	while (i < parsing->rows - 2)
	{
		while (j < parsing->cols - 1)
		{
			if (check_char(parsing->map[i][j]) == 1)
				return (1);
			if (parsing->map[i][j] == 'N' || \
				parsing->map[i][j] == 'W' || \
				parsing->map[i][j] == 'E' || parsing->map[i][j] == 'S')
				h++;
			j++;
		}
		j = 1;
		i++;
	}
	if (h > 1 || h == 0)
		return (1);
	return (0);
}

int	check_map(t_list *parsing)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (check_first_and_last(parsing) == 1)
		return (1);
	if (check_unwanted_characters(parsing) == 1)
		return (1);
	if (check_start_end(parsing) == 1)
		return (1);
	return (0);
}

char	*process_line(t_list *parsing, char *line, int *max_cols, int cols)
{
	t_process_line	arg;

	arg.start = 0;
	arg.end = cols - 1;
	while (line[arg.start] == '-' && arg.start <= arg.end)
		arg.start++;
	while (line[arg.end] == '-' && arg.end >= arg.start)
		arg.end--;
	arg.len = arg.end - arg.start + 1;
	if (arg.len > *max_cols)
		*max_cols = arg.len;
	arg.str = (char *)gc_malloc(&parsing->gc, (arg.len + 1) * sizeof(char));
	if (!arg.str)
		print_error(parsing, "Allocation fails!\n");
	arg.j = 0;
	while (arg.j < arg.len)
	{
		if (line[arg.start + arg.j] == ' ')
			arg.str[arg.j] = '-';
		else
			arg.str[arg.j] = line[arg.start + arg.j];
		arg.j++;
	}
	arg.str[arg.j] = '\0';
	return (arg.str);
}
