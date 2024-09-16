/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:46:50 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 00:34:00 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_list	*parsing_lst;

	parsing_lst = malloc(sizeof(t_list));
	if (parsing_lst == NULL)
		exit(1);
	if (argc != 2)
	{
		printf("invalid arguments !!\n");
		return (1);
	}
	parsing(parsing_lst, argv);
	return (0);
}
