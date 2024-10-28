/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:46:51 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 22:25:42 by ymakhlou         ###   ########.fr       */
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

void	free_list(t_list *parsing, t_pars *pars)
{
	size_t	i;

	if (!parsing)
		return ;
	if (pars)
		free_pars(pars);
	if (parsing->texture)
	{
		free_texture(parsing->texture);
	}
	if (parsing->map)
	{
		i = 0;
		while (parsing->map[i])
		{
			free(parsing->map[i]);
			i++;
		}
		free(parsing->map);
	}
	free(parsing);
}
