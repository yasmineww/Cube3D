/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:04:56 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/10/23 22:27:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
