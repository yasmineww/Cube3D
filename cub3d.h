/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:48:52 by youbihi           #+#    #+#             */
/*   Updated: 2024/09/22 15:32:25 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define CUBE_SIZE	32
# define W_HEIGHT	960
# define W_WIDTH	1600

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

typedef struct s_player
{
	double	x;
	double	y;
	int	size;
	int	turn;
	int	walk;
	double	rot_angle;
	int	rot_speed;
	double	move_speed;
}	t_player;

typedef struct s_mlx
{
	void	*init;
	void	*img;
}	t_mlx;

typedef struct s_data
{
	t_mlx		*mlx;
	t_player	*player;
	int			width;
	int			height;
	char		**map;
	int			rows;
	int			cols;
}	t_data;

typedef struct s_pars
{
	char				*value;
	struct s_pars		*next;
}	t_pars;

typedef struct s_texture
{
	char				*key;
	char				*value;
	struct s_texture	*next;
}	t_texture;

typedef struct s_list
{
	t_texture	*texture;
	char		**map;
	int			rows;
	int			cols;
}	t_list;

/*-------------------------------raycasting-------------------------------*/

void		data_init(t_data **data, t_list *parsing_lst);
void		render_window(void *param);
void		key_func(mlx_key_data_t datakey, void *param);

/*-------------------------------get_next_line-------------------------------*/

size_t		ft_strlen_get(char *s);
int			ft_line_len(char *str);
char		*ft_line_insert(char *return_line, char *all_line);
char		*line_maker(char *str);
char		*ft_read_lines(int fd, char *all_lines);
char		*get_next_line(int fd);
char		*ft_left_lines(char *all_lines);
char		*ft_strjoin_get(char *left_str, char *buff);

/*-------------------------------parsing-------------------------------*/

void		parsing(t_list *parsing, char **argv);
void		print_error(char *str);
t_pars		*allocate_pars(int *fd);
int			open_file(char *argv);
int			check_line(char *line);
int			skip_line(char *line);
t_pars		*init_parsing(char **argv, int *fd, char **line);
char		*process_parsing(t_pars *pars, int fd, char *line);
void		texture_syntax(char **arr, t_list *parsing_lst, t_pars *pars);
void		process_pars(t_list *parsing_lst, t_pars *pars);
void		clean_str(t_pars *pars);
t_texture	*create_node(void);
t_texture	*allocate_six_nodes(int i);
int			pars_leght(t_pars *pars);
void		init_texture(t_list *parsing_lst, t_pars *pars);
void		check_texture(t_list *parsing_lst, t_pars *pars);
void		free_and_error(t_list *parsing_lst, t_pars	*temp, char *str);
t_pars		*process_map(t_list *parsing_lst, int fd, char *line);
void		fill_map(char **arr, int cols, int rows, t_pars *pars);
char		**get_map(t_pars *tmp, int *num, t_list *parsing_lst);
void		check_for_tabs(t_list *parsing_lst, t_pars *pars);

/*-------------------------------utils-------------------------------*/

void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *str);
size_t		ft_strlen(const char *str);
char		**ft_custom_split(char const *s);
void		free_split(char **split);
void		free_list(t_list *list, t_pars *pars);
void		free_split(char **split);
char		*ft_custom_strdup(const char *str);
size_t		array_length(char **arr);
int			ft_strcmp(const char *s1, const char *s2);
void		free_pars(t_pars *pars);

#endif