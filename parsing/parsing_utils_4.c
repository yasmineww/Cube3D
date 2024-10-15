/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:43:14 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/15 19:29:10 by ymakhlou         ###   ########.fr       */
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

	temp = malloc(sizeof(t_pars));//unprotected malloc + there is 3 malloc for t_pars
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
			temp->next = malloc(sizeof(t_pars));//unprotected malloc + there is 3 malloc for t_pars
			temp = temp->next;
			temp->next = NULL;
		}
		else
			temp->next = NULL;
	}
	return (temp_pars);
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
