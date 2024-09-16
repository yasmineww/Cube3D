/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 01:40:26 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_texture_list(t_texture **temp, char *line, int i)
{
	if (i != 0)
	{
		(*temp)->next = allocat_texture();
		*temp = (*temp)->next;
	}
	(*temp)->value = ft_strdup(line);
	(*temp)->next = NULL;
}

void	process_parsing(t_list *parsing_lst, int fd, char *line, int i)
{
	t_texture	*temp;

	i = 0;
	temp = parsing_lst->texture;
	while (line != NULL || line[0] != '1')
	{
		line = read_next_line(fd, line);
		if (line == NULL)
			break ;
		update_texture_list(&temp, line, i);
		line = get_next_line(fd);
		i++;
	}
}

void	parsing(t_list *parsing_lst, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	init_parsing(parsing_lst, argv, &fd, &line);
	process_parsing(parsing_lst, fd, line, i);
	while (parsing_lst->texture)
	{
		printf("%s\n",parsing_lst->texture->value);
		parsing_lst->texture = parsing_lst->texture->next;
	}
}
