NAME = cub3d

SRCF = main.c libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c \
       libft/ft_toupper.c libft/ft_tolower.c libft/ft_bzero.c libft/ft_strncmp.c \
       libft/ft_memset.c libft/ft_memchr.c libft/ft_memcpy.c libft/ft_strchr.c \
       libft/ft_strnstr.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_memcmp.c libft/ft_strrchr.c \
       libft/ft_memmove.c libft/ft_atoi.c \
       libft/ft_strdup.c \
       libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
       libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c \
       libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_strlen.c \
       get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
       parsing/parsing.c parsing/parsing_utils.c parsing/parsing_utils_1.c parsing/parsing_utils_2.c parsing/parsing_utils_3.c \
       generale_utils/ft_custom_split.c generale_utils/free_split.c generale_utils/linked_list_free.c generale_utils/custom_strdup.c\
	   generale_utils/arr_lenght.c generale_utils/ft_strcmp.c

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
