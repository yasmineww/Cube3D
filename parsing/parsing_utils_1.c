/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:45:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/19 16:29:55 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_pars	*init_parsing(char **argv, int *fd, char **line)
{
	t_pars	*pars;

	*fd = open_file(argv[1]);
	*line = get_next_line(*fd);
	if (*line == NULL)
	{
		close(*fd);
		print_error("Empty file!\n");
	}
	pars = allocate_pars(fd);
	return (pars);
}

char	*process_parsing(t_pars *pars, int fd, char *line)
{
	int			i;
	t_pars		*temp;

	i = 0;
	temp = pars;
	while (line != NULL || line[0] != '1')
	{
		if (check_line(line) == 1)
			break ;
		else if (skip_line(line) == 1)
			line = get_next_line(fd);
		else
		{
			if (i != 0)
			{
				temp->next = allocate_pars(&fd);
				temp = temp->next;
			}
			temp->value = ft_strdup(line);
			temp->next = NULL;
			line = get_next_line(fd);
			i++;
		}
	}
	return (line);
}

void	texture_syntax(char **arr, t_list *parsing_lst, t_pars *pars)
{
	free_split(arr);
	free_list(parsing_lst, pars);
	ft_putstr_fd("Invalid map !\n", 2);
	exit(1);
}

void	process_pars(t_list *parsing_lst, t_pars *pars)
{
	t_pars		*temp;
	char		**arr;

	temp = pars;
	while (temp != NULL)
	{
		arr = ft_custom_split(temp->value);
		if (array_length(arr) != 2)
			texture_syntax(arr, parsing_lst, pars);
		temp = temp->next;
	}
}

void	clean_str(t_pars *pars)
{
	t_pars		*temp;
	char		*str;

	temp = pars;
	while (temp)
	{
		str = ft_custom_strdup(temp->value);// why custom???
		free(temp->value);
		temp->value = str;
		temp = temp->next;
	}
}
