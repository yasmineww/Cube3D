/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:31:17 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 05:48:43 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

t_pars	*allocat_pars(void)
{
	t_pars	*temp;

	temp = malloc(sizeof(t_pars));
	if (temp == NULL)
		print_error("Allocation fails !\n");
	temp->next = NULL;
	return (temp);
}

int open_file(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		print_error("opne faild !\n");
	return (fd);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line && (line[i] == ' ' || line[i] == '	'))
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
	while (line && (line[i] == ' ' || line[i] == '	'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}
