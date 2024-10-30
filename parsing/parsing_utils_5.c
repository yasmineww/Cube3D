/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:45:01 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/30 01:57:39 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture	*create_node(t_list *parsing)
{
	t_texture	*node;

	node = (t_texture *)gc_malloc(&parsing->gc, sizeof(t_texture));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

t_texture	*allocate_four_nodes(int i, t_list *parsing)
{
	t_texture	*head;
	t_texture	*current;
	t_texture	*new_node;

	head = NULL;
	current = NULL;
	while (i < 4)
	{
		new_node = create_node(parsing);
		if (!new_node)
			return (NULL);
		if (head == NULL)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		i++;
	}
	return (head);
}

int	pars_leght(t_pars *pars)
{
	t_pars	*temp;
	int		i;

	temp = pars;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	check_text(char *str)
{
	if (ft_strcmp(str, "C") == 0 || ft_strcmp(str, "F") == 0)
		return (1);
	return (0);
}

int	check_comma(char *str, t_list *parsing)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str[i])
	{
		if (str[i] == ',')
			b++;
		if (str[i] == '\t')
			print_error(parsing, "Invalid Map tab detected !\n");
		i++;
	}
	return (b);
}
