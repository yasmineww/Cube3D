/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/17 08:54:51 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parsing(t_list *parsing_lst, char **argv)
{
	int		fd;
	char	*line;
	t_pars	*pars;
	int		num;

	parsing_lst->texture = NULL;
	pars = init_parsing(argv, &fd, &line);
	line = process_parsing(pars, fd, line);
	clean_str(pars);
	parsing_lst->map = NULL;
	process_pars(parsing_lst, pars);
	init_texture(parsing_lst, pars);
	check_texture(parsing_lst, pars);
	free_pars(pars);
	pars = process_map(parsing_lst, fd, line);
	clean_str(pars);
	check_for_tabs(parsing_lst, pars);
	parsing_lst->map = get_map(pars, &num);
}
