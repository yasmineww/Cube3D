/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:46:50 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/23 11:41:09 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	gc_free_all(t_garbage **list)
{
	t_garbage	*current;
	t_garbage	*next_node;

	current = *list;
	while (current)
	{
		next_node = current->next;
		free(current->ptr);
		current->ptr = NULL;
		free(current);
		current = next_node;
	}
	*list = NULL;
}

void	gc_lstadd_front(t_garbage **list, t_garbage *new_node)
{
	if (!new_node)
		return ;
	if (!list)
		return ;
	new_node->next = *list;
	*list = new_node;
}

t_garbage	*gc_lstnew(void *ptr, t_garbage **list)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		gc_free_all(list);
		exit (1);
	}
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

void	*gc_malloc(t_garbage **list, size_t size)
{
	t_garbage	*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		gc_free_all(list);
		exit(1);
	}
	new_node = gc_lstnew(ptr, list);
	gc_lstadd_front(list, new_node);
	return (ptr);
}

void	check_file_extention(char *file, t_list	*parsing_lst)
{
	char	**arr;

	arr = ft_split(file, '.', parsing_lst);
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
	parsing_lst = malloc(sizeof(t_list));
	check_file_extention(argv[1], parsing_lst);
	if (parsing_lst == NULL)
		exit(1);
	parsing(parsing_lst, argv);
	data_init(&data, parsing_lst);
	mlx_loop_hook(data->mlx->init, &render_window, data);
	mlx_key_hook(data->mlx->init, &key, data);
	mlx_set_cursor_mode(data->mlx->init, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(data->mlx->init, &mouse, data);
	mlx_mouse_hook(data->mlx->init, mouse_click_handler, data);
	mlx_loop(data->mlx->init);
	gc_free_all(&parsing_lst->gc);
	return (0);
}
