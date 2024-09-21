/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:46:50 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/21 11:45:54 by ymakhlou         ###   ########.fr       */
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
		print_error("Invalid file extensions !\n");
	}
	free_split(arr);
}

int	main(int argc, char **argv)
{
	t_list	*parsing_lst;
	t_data	*data;

	if (argc != 2)
	{
		print_error("Invalid arguments !!\n");
		return (1);
	}
	check_file_extention(argv[1]);
	parsing_lst = malloc(sizeof(t_list));
	if (parsing_lst == NULL)
		exit(1);
	parsing(parsing_lst, argv);
	data_init(&data, parsing_lst);
	mlx_loop_hook(data->mlx->init, &render_window, data);
	mlx_key_hook(data->mlx->init, &key_func, data);
	mlx_loop(data->mlx->init);
	return (0);
}
