/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:50:01 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/27 11:36:38 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_str(t_pars *pars)
{
	t_pars		*temp;
	char		*str;

	temp = pars;
	while (temp)
	{
		str = ft_custom_strdup(temp->value);
		free(temp->value);
		temp->value = str;
		temp = temp->next;
	}
}

int	check_unwanted_characters(t_list *parsing_lst)
{
	int	i;
	int	j;
	int	h;

	i = 1;
	j = 1;
	h = 0;
	while (i < parsing_lst->rows - 2)
	{
		while (j < parsing_lst->cols - 1)
		{
			if (check_char(parsing_lst->map[i][j]) == 1)
				return (1);
			if (parsing_lst->map[i][j] == 'N' || \
				parsing_lst->map[i][j] == 'W' || \
				parsing_lst->map[i][j] == 'E' || parsing_lst->map[i][j] == 'S')
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

int	check_map(t_list *parsing_lst)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (check_first_and_last(parsing_lst) == 1)
		return (1);
	if (check_unwanted_characters(parsing_lst) == 1)
		return (1);
	if (check_start_end(parsing_lst) == 1)
		return (1);
	return (0);
}