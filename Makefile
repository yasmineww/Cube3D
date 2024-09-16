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
       parsing/parsing.c parsing/parsing_utils.c \
       generale_utils/ft_custom_split.c generale_utils/free_split.c generale_utils/linked_list_free.c generale_utils/custom_strdup.c

OBJDIR = build

OBJF = $(addprefix $(OBJDIR)/, $(SRCF:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

READLINEDIR = $(shell brew --prefix readline)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJF)
	$(CC) $(CFLAGS) $(OBJF) -o $(NAME)

$(OBJDIR)/%.o: %.c cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(READLINEDIR)/include

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(OBJF): | $(OBJDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)