/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:50:13 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/19 16:05:43 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture	*create_node(void)
{
	t_texture	*node;

	node = (t_texture *)malloc(sizeof(t_texture));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

t_texture	*allocate_six_nodes(int i)
{
	t_texture	*head;
	t_texture	*current;
	t_texture	*new_node;

	head = NULL;
	current = NULL;
	while (i < 6)
	{
		new_node = create_node();
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

void	init_texture(t_list *parsing_lst, t_pars *pars)
{
	char		**arr;
	t_texture	*temp;

	if (pars_leght(pars) > 6)//leak fd
	{
		free_list(parsing_lst, pars);
		print_error("Invalid map !\n");
	}
	parsing_lst->texture = allocate_six_nodes(0);
	temp = parsing_lst->texture;
	while (pars)
	{
		arr = ft_custom_split(pars->value);
		temp->key = ft_strdup(arr[0]);
		temp->value = ft_strdup(arr[1]);
		free_split(arr);
		temp = temp->next;
		pars = pars->next;
	}
}

void	check_texture(t_list *parsing_lst, t_pars *pars)
{
	t_texture	*temp;

	temp = parsing_lst->texture;
	while (temp)
	{
		if (ft_strcmp(temp->key, "EA") != 0 && \
			ft_strcmp(temp->key, "NO") != 0 && \
			ft_strcmp(temp->key, "C") != 0 && \
			ft_strcmp(temp->key, "F") != 0 && \
			ft_strcmp(temp->key, "SO") != 0 && ft_strcmp(temp->key, "WE") != 0)
		{
			free_list(parsing_lst, pars);// leak fd
			print_error("Invalid map !\n");
		}
		temp = temp->next;
	}
}
