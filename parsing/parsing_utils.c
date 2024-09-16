/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:31:17 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 01:32:47 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

t_texture	*allocat_texture(void)
{
	t_texture	*temp;

	temp = malloc(sizeof(t_texture));
	if (temp == NULL)
		print_error("Allocation fails !\n");
	temp->next = NULL;
	return (temp);
}

int	open_file(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		print_error("opne faild !\n");
	return (fd);
}

void	init_parsing(t_list *parsing_lst, char **argv, int *fd, char **line)
{
	*fd = open_file(argv[1]);
	*line = get_next_line(*fd);
	if (*line == NULL)
		print_error("Empty file!\n");
	parsing_lst->texture = allocat_texture();
}

char	*read_next_line(int fd, char *line)
{
	while (ft_strncmp(line, "\n", 1) == 0)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '1')
			return (NULL);
	}
	return (line);
}
