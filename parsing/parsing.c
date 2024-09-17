/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:22:08 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/17 06:55:00 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_pars	*init_parsing(char **argv, int *fd, char **line)
{
	t_pars	*pars;

	*fd = open_file(argv[1]);
	*line = get_next_line(*fd);
	if (*line == NULL)
		print_error("Empty file!\n");
	pars = allocat_pars();
	return (pars);
}

char	*process_parsing(t_pars *pars, int fd, char *line)
{
	int			i;
	t_pars		*temp;

	i = 0;
	temp = pars;
	while (line != NULL || line[0] != '1')
	{
		if (check_line(line) == 1)
			break ;
		else if (skip_line(line) == 1)
			line = get_next_line(fd);
		else
		{
			if (i != 0)
			{
				temp->next= allocat_pars();
				temp = temp->next;
			}
			temp->value = ft_strdup(line);
			temp->next = NULL;
			line = get_next_line(fd);
			i++;
		}
		if (line == NULL || line[0] == '1')
			break ;
	}
	return(line);
}

void	handel_shit(char **arr, t_list *parsing_lst, t_pars *pars)
{
	free_split(arr);
	free_list(parsing_lst, pars);
	ft_putstr_fd("Invalid map !\n", 2);
	exit(1);
}

void	process_pars(t_list *parsing_lst, t_pars *pars)
{
	t_pars		*temp;
	char		**arr;

	temp = pars;
	while (temp != NULL)
	{
		arr = ft_custom_split(temp->value);
		if (array_length(arr) != 2)
			handel_shit(arr,parsing_lst, pars);
		temp = temp->next;
	}
}

void	clean_str(t_pars *pars)
{
	t_pars		*temp;
	char		*str;

	temp = pars;
	while (temp)
	{
		str = ft_custom_strdup(temp->value);
		free(temp->value);
		temp->value = str;
		temp = temp->next;
	}
}

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

t_texture	*allocate_six_nodes(void)
{
	t_texture	*head;
	t_texture	*current;
	t_texture	*new_node;
	int			i;

	i = 0;
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

int pars_leght(t_pars *pars)
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

	if (pars_leght(pars) > 6)
	{
		free_list(parsing_lst, pars);
		print_error("Invalid map !\n");
	}
	parsing_lst->texture = allocate_six_nodes();
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
			free_list(parsing_lst, pars);
			print_error("Invalid map ! \n");
		}
		temp = temp->next;
	}
}

t_pars	*process_map(t_list *parsing_lst, int fd, char *line)
{
	t_pars	*temp_pars;
	t_pars	*temp;
	int		i;

	temp = malloc(sizeof(t_pars));
	temp_pars = temp;
	i = 0;
	(void)parsing_lst;
	if (line == NULL)
	{
		free_list(parsing_lst, NULL);
		print_error("Invalid map !\n");
	}
	while (line && ft_strcmp(line, "\n") != 0 && skip_line(line) == 0)
	{
		temp->value = ft_strdup(line);
		line = get_next_line(fd);
		if (line != NULL && ft_strcmp(line, "\n") != 0 && skip_line(line) == 0)
		{
			temp->next = malloc(sizeof(t_pars));
			temp = temp->next;
			temp->next = NULL;
		}
		else
			temp->next = NULL;
	}
	return (temp_pars);
}

void	fill_map(char **arr, int cols, int rows, t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rows)
	{
		j = 0;
		while (pars->value[j] && j < cols)
		{
			arr[i][j] = pars->value[j];
			j++;
		}
		while (j < cols)
		{
			arr[i][j] = ' ';
			j++;
		}
		pars = pars->next;
		i++;
	}
}

char	**get_map(t_pars *tmp, int *num)
{
	size_t		rows;
	size_t		cols;
	char		**arr;
	size_t		i;
	t_pars		*values;

	rows = 0;
	i = 0;
	cols = 0;
	values = tmp;
	while (tmp)
	{
		if (cols < ft_strlen(tmp->value))
			cols = ft_strlen(tmp->value);
		rows++;
		tmp = tmp->next;
	}
	arr = (char **)malloc(rows * sizeof(char *));
	while (i < rows)
	{
		arr[i] = (char *)malloc(cols * sizeof(char));
		i++;
	}
	*num = cols;
	fill_map(arr, cols, rows, values);
	return (arr);
}

void	check_for_tabs(t_list *parsing_lst, t_pars *pars)
{
	int		i;
	t_pars	*temp;

	i = 0;
	temp = pars;
	while (temp)
	{
		while (temp->value[i])
		{
			if (temp->value[i] == '\t')
			{
				free_list(parsing_lst, pars);
				print_error("Invalid Map : Tabs detected !\n");
			}
			i++;
		}
		temp = temp->next;
		i = 0;
	}
}

void	parsing(t_list *parsing_lst, char **argv)
{
	int		fd;
	char	*line;
	t_pars	*pars;
	int		num;

	parsing_lst->texture = NULL;
	pars = init_parsing(argv, &fd, &line);
	line = process_parsing(pars, fd, line);
	clean_str(pars);
	parsing_lst->map = NULL;
	process_pars(parsing_lst, pars);
	init_texture(parsing_lst, pars);
	check_texture(parsing_lst, pars);
	free_pars(pars);
	pars = process_map(parsing_lst, fd, line);
	clean_str(pars);
	check_for_tabs(parsing_lst, pars);
	parsing_lst->map = get_map(pars, &num);
	size_t b = 0;
	size_t c = 0;
	while (b < 16)
	{
		while (c < 38)
		{
			printf("%c", parsing_lst->map[b][c]);
			c++;
		}
		printf(".");
		c = 0;
		b++;
		printf("\n");
	}
}
