/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbihi <youbihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:21:42 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/22 14:31:12 by youbihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_line_insert(char *return_line, char *all_line)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (all_line[i] != '\n')
	{
		if (all_line[i] == '\0')
			i++;
		return_line[index++] = all_line[i++];
	}
	return_line[index] = '\n';
	return (return_line);
}

char	*ft_strchr_get(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_get(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*line_maker(char *all_lines, t_list *parsing)
{
	int		line_len;
	char	*return_line;

	line_len = 0;
	if (!all_lines[line_len])
		return (NULL);
	while (all_lines[line_len] && all_lines[line_len] != '\n')
		line_len++;
	return_line = (char *)gc_malloc(&parsing->gc, sizeof(char) * (line_len + 2));
	if (!return_line)
		return (NULL);
	line_len = 0;
	while (all_lines[line_len] && all_lines[line_len] != '\n')
	{
		return_line[line_len] = all_lines[line_len];
		line_len++;
	}
	if (all_lines[line_len] == '\n')
	{
		return_line[line_len] = all_lines[line_len];
		line_len++;
	}
	return_line[line_len] = '\0';
	return (return_line);
}

char	*ft_read_lines(int fd, char *all_lines, t_list *parsing)
{
	int		num_of_read;
	char	*buff;

	buff = (char *)gc_malloc(&parsing->gc, BUFFER_SIZE + 1 * (sizeof(char)));
	if (!buff)
		return (NULL);
	num_of_read = 1;
	while (!ft_strchr_get(all_lines, '\n') && num_of_read != 0)
	{
		num_of_read = read(fd, buff, BUFFER_SIZE);
		if (num_of_read == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[num_of_read] = '\0';
		all_lines = ft_strjoin_get(all_lines, buff, parsing);
		if (all_lines == NULL)
			print_error("Allocation Failed for columns!\n");
	}
	free (buff);
	return (all_lines);
}

char	*get_next_line(int fd, t_list *parsing)
{
	char		*line_to_write;
	static char	*all_lines;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, all_lines, 0) < 0)
	{
		free(all_lines);
		all_lines = NULL;
		return (0);
	}
	all_lines = ft_read_lines(fd, all_lines, parsing);
	if (!all_lines)
	{
		return (NULL);
	}
	line_to_write = line_maker(all_lines, parsing);
	all_lines = ft_left_lines(all_lines, parsing);
	return (line_to_write);
}
