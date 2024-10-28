/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:45:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 18:08:22 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_pars	*init_parsing(char **argv, int *fd, char **line, t_list *parsing)
{
	t_pars	*pars;

	*fd = open_file(argv[1]);
	*line = get_next_line(*fd, parsing);
	if (*line == NULL)
	{
		close(*fd);
		print_error("Empty file!\n");
	}
	pars = allocate_pars(fd, parsing);
	return (pars);
}

char	*get_line(t_pars **temp, t_line_arg var, char *line, t_list *parsing)
{
	if (*var.i != 0)
	{
		(*temp)->next = allocate_pars(&var.fd, parsing);
		*temp = (*temp)->next;
	}
	(*temp)->value = ft_strdup(line, parsing);
	(*temp)->next = NULL;
	line = get_next_line(var.fd, parsing);
	(*var.i)++;
	return (line);
}

char	*process_parsing(t_pars *pars, int fd, char *line, t_list *parsing)
{
	int			i;
	int			b;
	t_pars		*temp;
	t_line_arg	var;

	b = 0;
	i = 0;
	temp = pars;
	while (line != NULL && line[0] != '1')
	{
		var.i = &i;
		var.fd = fd;
		if (check_line(line) == 1)
			break ;
		else if (skip_line(line) == 1)
			line = get_next_line(fd, parsing);
		else
			line = get_line(&temp, var, line, parsing);
		if (line == NULL)
			print_error("Invalid map\n");
		b++;
	}
	if (b < 6)
		print_error("Invalid Map!\n");
	return (line);
}

void	texture_syntax(char **arr, t_list *parsing_lst, t_pars *pars)
{
	(void)arr;
	(void)parsing_lst;
	(void)pars;
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
		arr = split_texture(temp->value, parsing_lst);
		if (array_length(arr) != 2)
			texture_syntax(arr, parsing_lst, pars);
		temp = temp->next;
	}
}
