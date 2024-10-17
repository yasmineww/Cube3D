/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:31:17 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/17 15:44:01 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(1);
}

t_pars	*allocate_pars(int *fd)
{
	t_pars	*temp;

	temp = malloc(sizeof(t_pars));
	if (temp == NULL)
	{
		close(*fd);
		print_error("Allocation fails !\n");
	}
	temp->next = NULL;
	return (temp);
}

int	open_file(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		print_error("Open syscall failed\n");
	return (fd);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	skip_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (1);
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}
