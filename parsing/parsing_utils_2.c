/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:50:13 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/24 18:11:04 by youbihi          ###   ########.fr       */
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

t_texture	*allocate_four_nodes(int i)
{
	t_texture	*head;
	t_texture	*current;
	t_texture	*new_node;

	head = NULL;
	current = NULL;
	while (i < 4)
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

int check_text(char *str)
{
	if (ft_strcmp(str, "C") == 0 || ft_strcmp(str, "F") == 0)
		return (1);
	return (0);
}

int	check_comma(char *str)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str[i])
	{
		if (str[i] == ',')
			b++;
		if (str[i] == ' ')
			print_error("Invalid Map Space detected !\n");
		i++;
	}
	return (b);
}

int	num_is_big(char *str)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(str, ',');
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > 3)
			return (1);
		if (ft_atoi(arr[i]) > 255 || ft_atoi(arr[i]) < 1)
			return (1);
		i++;
	}
	return (0);
}

void	get_color(t_list *parsing_lst, char **arr)
{
	char	**nums;

	if (check_comma(arr[1]) > 2)
		print_error("Invalid Map More or less than 2 comma! \n");
	if (num_is_big(arr[1]) == 1)
		print_error("Invalid Map Color map number not valid !\n");
	nums = ft_split(arr[1], ',');
	if (ft_strcmp(arr[0], "C") == 0)
	{
		parsing_lst->texture->C[0] = ft_atoi(nums[0]);
		parsing_lst->texture->C[1] = ft_atoi(nums[1]);
		parsing_lst->texture->C[2] = ft_atoi(nums[2]);
	}
	else
	{
		parsing_lst->texture->F[0] = ft_atoi(nums[0]);
		parsing_lst->texture->F[1] = ft_atoi(nums[1]);
		parsing_lst->texture->F[2] = ft_atoi(nums[2]);
	}
}

void	init_texture(t_list *parsing_lst, t_pars *pars)
{
	char		**arr;
	t_texture	*temp;

	if (pars_leght(pars) > 6 || pars_leght(pars) < 6)
	{
		free_list(parsing_lst, pars);
		print_error("Invalid map !\n");
	}
	parsing_lst->texture = allocate_four_nodes(0);
	temp = parsing_lst->texture;
	while (pars)
	{
		arr = split_texture(pars->value);
		if (check_text((arr[0])) != 1)
		{
			temp->key = ft_strdup(arr[0]);
			temp->value = ft_strdup(arr[1]);
			temp = temp->next;
		}
		else
			get_color(parsing_lst, arr);
		free_split(arr);
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
			free_list(parsing_lst, pars);
			print_error("Invalid map !\n");
		}
		temp = temp->next;
	}
}
