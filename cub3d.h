/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:48:52 by youbihi           #+#    #+#             */
/*   Updated: 2024/10/30 01:13:07 by ymakhlou         ###   ########.fr       */
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
# define M_SIZE		22
# define W_HEIGHT	960
# define W_WIDTH	1600
# define M_WIDTH	320
# define M_HEIGHT	192

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_doors
{
	int					x;
	int					y;
	int					is_open;
	struct s_doors		*next;
}	t_door;

typedef struct s_ray
{
	double	pov;
	double	ray_angle;
	double	distance_v;
	double	distance_h;
	int		door;
	int		door_h;
	int		door_v;
	int		up;
	int		down;
	int		left;
	int		right;
	int		is_v;
}	t_ray;

typedef struct s_player
{
	int		x;
	int		y;
	int		rayon;
	double	turn;
	double	walk;
	double	view_angle;
	double	move_speed;
}	t_player;

typedef struct s_mlx
{
	void			*init;
	void			*img;
	mlx_texture_t	*ea;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*door;
}	t_mlx;

typedef struct s_wall_render
{
	mlx_texture_t	*texture;
	int				*arr;
	double			factor;
	double			y_offset;
	double			x_offset;
}	t_wall_render;

typedef struct s_texture
{
	int					c[3];
	int					f[3];
	char				*key;
	char				*value;
	struct s_texture	*next;
}	t_texture;

typedef struct s_animation
{
	uint32_t		y;
	uint32_t		x;
	mlx_texture_t	*frame;
	uint32_t		pixel_index;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	uint32_t		color;
}	t_animation;

typedef struct s_data
{
	t_mlx			*mlx;
	t_player		*player;
	t_ray			*ray;
	t_texture		*texture;
	t_animation		*animation;
	mlx_texture_t	*images[6];
	mlx_texture_t	*cross_aim;
	char			**map;
	int				rows;
	int				cols;
	int				mouse_clicked;
	int				current_frame;
	int				animation_phase;
	int				open;
	int				c;
	int				f;
	t_door			*doors;
}	t_data;

typedef struct s_line
{
	int		start;
	int		end;
	int		len;
	char	*str;
	int		j;
}	t_process_line;

typedef struct s_map
{
	int		new_rows;
	char	**new_map;
	int		i;
	int		row_index;
	int		max;
}	t_map_create;

typedef struct s_pars
{
	char				*value;
	struct s_pars		*next;
}	t_pars;

typedef struct s_list
{
	t_texture	*texture;
	char		**map;
	double		view_angle;
	int			rows;
	int			cols;
	int			x;
	int			y;
	int			fd;
	t_garbage	*gc;
	t_door		*doors;
}	t_list;

typedef struct s_process_map
{
	size_t		rows;
	size_t		cols;
	char		**arr;
	size_t		i;
	t_pars		*values;
}	t_process_map;

typedef struct s_wall_var
{
	t_wall_render	var;
	double			top;
	double			bot;
	double			wall_height;
}	t_wall_var;

typedef struct s_map_handling
{
	t_pars	*temp_pars;
	t_pars	*temp;
}	t_map_handling;

typedef struct s_pixel_data
{
	int	dy;
	int	dx;
	int	scaled_x;
	int	scaled_y;
}	t_pixel_data;

typedef struct s_keys
{
	int		x;
	int		y;
	int		window_width;
	int		window_height;
	int		center_x;
	int		center_y;
}	t_keys;

typedef struct s_line_arg
{
	int	*i;
	int	fd;
}	t_line_arg;

typedef struct s_position_dor
{
	int		x;
	int		y;
}	t_position_dor;

typedef struct s_wall_collision
{
	int	x_min;
	int	x_max;
	int	y_min;
	int	y_max;
}	t_wall_collision;

/*-------------------------------textures-------------------------------*/
void			*gc_malloc(t_garbage **list, size_t size);
void			gc_free_all(t_garbage **list);
int				reverse(int c);
void			draw_sprite(t_data *data);
void			mouse_click_handler(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);
void			render_top(t_data *data, int nmbr_rays, double top);
double			get_x_offset(mlx_texture_t *ea, t_data *data);
void			render_bottom(t_data *data, int nmbr_rays, double bot);
void			load_textures(t_data *data);
mlx_texture_t	*get_vertical_texture(t_data *data);

/*-------------------------------raycasting-------------------------------*/

void			data_init(t_data **data, t_list *parsing);
void			render_window(void *param);
void			key(mlx_key_data_t datakey, void *param);
void			mouse(double mouse_x, double mouse_y, void *param);
int				is_wall(t_data *data, double x, double y);
void			ray_casting(t_data *data);
void			draw_ray(t_data *data, double distance);
void			render_wall(t_data *data, double distance, int nmbr_rays);
float			normalize(float angle, t_ray *ray);
void			my_put_pixel(t_data *data, int x, int y, int color);
void			draw_ray(t_data *data, double distance);
void			move_player(t_player *player, t_data *data);
void			create_player(t_data *data);
void			toggle_door_state(t_door *door);

/*-------------------------------get_next_line-------------------------------*/

size_t			ft_strlen_get(char *s);
int				ft_line_len(char *str);
char			*ft_line_insert(char *return_line, char *all_line);
char			*line_maker(char *all_lines, t_list *parsing);
char			*ft_read_lines(int fd, char *all_lines, t_list *parsing);
char			*get_next_line(int fd, t_list *parsing);
char			*ft_left_lines(char *all_lines, t_list *parsing);
char			*ft_strjoin_get(char *left_str, char *buff, t_list *parsing);

/*-------------------------------parsing-------------------------------*/

int				check_first_and_last(t_list *parsing);
int				check_character(char c);
void			parsing(t_list *data, char **argv);
void			print_error(t_list *parsing, char *str);
t_pars			*allocate_pars(t_list *parsing);
int				open_file(char *argv);
int				check_line(char *line);
int				skip_line(char *line);
t_pars			*init_parsing(char **argv, char **line, \
					t_list *parsing);
char			*process_parsing(t_pars *pars, char *line,
					t_list *parsing);
void			process_pars(t_list *parsing, t_pars *pars);
void			clean_str(t_pars *pars, t_list *parsing);
t_texture		*create_node(t_list *parsing);
int				pars_leght(t_pars *pars);
void			init_texture(t_list *parsing, t_pars *pars);
void			check_texture(t_list *parsing, t_pars *pars);
void			free_and_error(t_list *parsing, t_pars	*temp, char *str);
t_pars			*process_map(t_list *parsing, char *line);
void			fill_map(char **arr, int cols, int rows, t_pars *pars);
char			**get_map(t_pars *tmp, int *num, t_list *parsing);
void			check_for_tabs(t_list *parsing, t_pars *pars);
int				check_map(t_list *parsing);
int				check_comma(char *str, t_list *parsing);
t_texture		*allocate_four_nodes(int i, t_list *parsing);
int				check_text(char *str);
int				check_char(char c);
int				check_start_end(t_list *lst);
char			*process_line(t_list *parsing, char *line, int *max_cols,
					int cols);
void			process_pixel_data(t_data *data, int flag);
void			process_sprite_frame(t_data *data, \
				t_animation *animation, int flag);
void			manage_animation_frame(t_data *data);
void			check_door(t_list *parsing, int x, int y);
char			**create_map(t_list *parsing, char **map, \
					int *old_rows, int *cols);
void			get_player_position(t_list *parsing);
void			process_door(t_list *parsing, t_position_dor var, \
					int *c, t_door **door);
void			check_result(char *str, t_list *parsing);

/*-------------------------------utils-------------------------------*/

int				ft_atoi(const char *s);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c, t_list	*parsing);
char			*ft_strdup(const char *str, t_list *parsing);
size_t			ft_strlen(const char *str);
void			free_list(t_list *parsing, t_pars *pars);
void			free_split(char **split);
char			*ft_custom_strdup(const char *str, t_list *parsing);
size_t			array_length(char **arr);
int				ft_strcmp(const char *s1, const char *s2);
void			free_pars(t_pars *pars);
char			**split_texture(char const *s, t_list *parsing);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n, t_list *parsing);
void			*ft_memcpy(void *destination, const void *source, size_t num);

#endif