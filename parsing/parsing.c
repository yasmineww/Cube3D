/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/20 11:48:15 by ymakhlou         ###   ########.fr       */
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
	parsing_lst->map = NULL;
	pars = init_parsing(argv, &fd, &line);
	line = process_parsing(pars, fd, line);
	clean_str(pars);
	process_pars(parsing_lst, pars);
	init_texture(parsing_lst, pars);
	check_texture(parsing_lst, pars);
	free_pars(pars);
	pars = process_map(parsing_lst, fd, line);
	clean_str(pars);
	check_for_tabs(parsing_lst, pars);
	parsing_lst->map = get_map(pars, &num, parsing_lst);
	free_pars(pars);
	close(fd);
}
