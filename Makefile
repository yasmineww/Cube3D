NAME = cub3d

SRCF = main.c utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strdup.c utils/ft_strlen.c utils/split_texture.c \
       get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
       parsing/parsing.c parsing/parsing_utils.c parsing/parsing_utils_1.c parsing/parsing_utils_2.c parsing/parsing_utils_3.c\
	   parsing/parsing_utils_4.c parsing/parsing_utils_5.c parsing/parsing_utils_6.c parsing/map_checking.c \
	   utils/free_split.c utils/linked_list_free.c utils/custom_strdup.c\
	   utils/arr_lenght.c utils/ft_strcmp.c utils/ft_atoi.c utils/ft_strjoin.c utils/ft_itoa.c utils/ft_memcpy.c\
	   raycasting/data_init.c raycasting/game.c raycasting/key_bindings.c raycasting/raycasting.c raycasting/render_walls.c\
	   raycasting/texture.c

OBJF = $(addprefix $(OBJDIR)/, $(SRCF:.c=.o))

OBJDIR = build

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
FLMLX	= -framework Cocoa -framework OpenGL -framework IOKit
LFLAG	= MLX42/libmlx42.a -lglfw -L/Users/$(USER)/.brew/opt/glfw/lib/

READLINEDIR = $(shell brew --prefix readline)

all: $(NAME)

$(OBJDIR)/%.o: %.c cub3d.h
	@mkdir -p $(dir $@)
	@(cc $(CFLAGS) -c $< -o $@ -I $(READLINEDIR)/include)
	@printf "\r\033[K\033[33mcompiling...\033[0m"

$(NAME): $(OBJF)
	@(cc $(CFLAGS) $(FLMLX) $(LFLAG) $(OBJF) -o $(NAME))
	@printf "\r\033[K\033[32mcub3d compiled\033[0m\n"

clean:
	@(rm -rf $(OBJDIR))
	@printf "\r\033[K\033[31mRemove Object Files\033[0m\n"

fclean: clean
	@(rm -rf $(NAME))
	@printf "\r\033[K\033[31mRemove executable\033[0m\n"

re: fclean all
