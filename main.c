/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:46:50 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 22:31:23 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_extention(char *file, t_list	*parsing)
{
	char	**arr;

	arr = ft_split(file, '.', parsing);
	if (array_length(arr) != 2 || ft_strcmp(arr[1], "cub") != 0)
	{
		free_split(arr);
		ft_putstr_fd("Error\n Invalid file extensions !\n", 2);
		exit(1);
	}
	free_split(arr);
}

void	close_window(void *param)
{
	t_data	*data;

	data = param;
	mlx_delete_image(data->mlx->init, data->mlx->img);
	mlx_close_window(data->mlx->init);
	printf("Sad to see you leave :(\n");
	exit(1);
}

void f(){
	system("leaks cub3D");
	system("lsof -c cub3D");
}

int	main(int argc, char **argv)
{
	t_list	*parsing_lst;
	t_data	*data;

	atexit(f);
	if (argc != 2)
	{
		ft_putstr_fd("Error\n Invalid arguments !!\n", 2);
		exit(1);
	}
	parsing_lst = malloc(sizeof(t_list));
	if (!parsing_lst)
		exit(1);
	check_file_extention(argv[1], parsing_lst);
	parsing(parsing_lst, argv);
	data_init(&data, parsing_lst);
	mlx_loop_hook(data->mlx->init, &render_window, data);
	mlx_key_hook(data->mlx->init, &key, data);
	mlx_set_cursor_mode(data->mlx->init, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(data->mlx->init, &mouse, data);
	mlx_mouse_hook(data->mlx->init, mouse_click_handler, data);
	mlx_close_hook(data->mlx->init, &close_window, data);
	mlx_loop(data->mlx->init);
	gc_free_all(&parsing_lst->gc);
	return (0);
}
