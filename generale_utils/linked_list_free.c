/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:46:51 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/16 06:19:29 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_pars(t_pars *pars)
{
	t_pars	*tmp;

	while (pars)
	{
		tmp = pars->next;
		if (pars->value)
			free(pars->value);
		free(pars);
		pars = tmp;
	}
}

void	free_texture(t_texture *texture)
{
	t_texture	*tmp;

	while (texture)
	{
		tmp = texture->next;
		if (texture->key)
			free(texture->key);
		if (texture->value)
			free(texture->value);
		free(texture);
		texture = tmp;
	}
}

void	free_list(t_list *list, t_pars *pars)
{
	size_t	i;

	if (!list)
		return ;
	if (pars)
		free_pars(pars);
	if (list->texture)
		free_texture(list->texture);
	if (list->map)
	{
		i = 0;
		while (list->map[i])
		{
			free(list->map[i]);
			i++;
		}
		free(list->map);
	}
	free(list);
}
