/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:46:50 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 06:40:21 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_extention(char *file)
{
	char	**arr;

	arr = ft_split(file, '.');
	if (array_length(arr) != 2 || ft_strcmp(arr[1], "cub") != 0)
	{
		free_split(arr);
		print_error("invalid file extensions !\n");
	}
}

int	main(int argc, char **argv)
{
	t_list	*parsing_lst;

	if (argc != 2)
	{
		printf("invalid arguments !!\n");
		return (1);
	}
	check_file_extention(argv[1]);
	parsing_lst = malloc(sizeof(t_list));
	if (parsing_lst == NULL)
		exit(1);
	parsing(parsing_lst, argv);
	return (0);
}
