/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:50:13 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/28 18:11:14 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	num_len(char *str)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		i++;
		b++;
	}
	return (b);
}

int	num_is_big(char *str, t_list *parsing_lst)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(str, ',', parsing_lst);
	while (arr[i])
	{
		if (num_len(arr[i]) > 3)
			return (1);
		if (ft_atoi(arr[i]) > 255 || ft_atoi(arr[i]) < 0)
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
	if (num_is_big(arr[1], parsing_lst) == 1)
		print_error("Invalid Map Color map number not valid !\n");
	nums = ft_split(arr[1], ',', parsing_lst);
	if (ft_strcmp(arr[0], "C") == 0)
	{
		if (nums[0] == NULL || nums[1] == NULL || nums[2] == NULL)
			print_error("invalid Map !");
		parsing_lst->texture->c[0] = ft_atoi(nums[0]);
		parsing_lst->texture->c[1] = ft_atoi(nums[1]);
		parsing_lst->texture->c[2] = ft_atoi(nums[2]);
	}
	else
	{
		if (nums[0] == NULL || nums[1] == NULL || nums[2] == NULL)
			print_error("invalid Map !");
		parsing_lst->texture->f[0] = ft_atoi(nums[0]);
		parsing_lst->texture->f[1] = ft_atoi(nums[1]);
		parsing_lst->texture->f[2] = ft_atoi(nums[2]);
	}
}

void	init_texture(t_list *parsing_lst, t_pars *pars)
{
	char		**arr;
	t_texture	*temp;

	if (pars_leght(pars) > 6 || pars_leght(pars) < 6)
		print_error("Invalid map !\n");
	parsing_lst->texture = allocate_four_nodes(0, parsing_lst);
	temp = parsing_lst->texture;
	while (pars)
	{
		arr = split_texture(pars->value, parsing_lst);
		if ((arr[0][0] == 'F' || arr[0][0] == 'C') && \
			ft_strcmp(arr[1], "") == 0)
			print_error("Invalid Map !");
		if (check_text((arr[0])) != 1)
		{
			temp->key = ft_strdup(arr[0], parsing_lst);
			temp->value = ft_strdup(arr[1], parsing_lst);
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

	(void)pars;
	temp = parsing_lst->texture;
	while (temp)
	{
		if (ft_strcmp(temp->key, "EA") != 0 && \
			ft_strcmp(temp->key, "NO") != 0 && \
			ft_strcmp(temp->key, "C") != 0 && \
			ft_strcmp(temp->key, "F") != 0 && \
			ft_strcmp(temp->key, "SO") != 0 && ft_strcmp(temp->key, "WE") != 0)
			print_error("Invalid map !\n");
		temp = temp->next;
	}
}
