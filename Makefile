NAME	=	minishell

SRC	=	main.c \
		get_next_line_utils.c \
		get_next_line.c \
		get_pwd.c \
		print_flowers.c \
		get_echo.c \
		parsing.c \
		tokens.c \
		utils_matrix.c \
		utils_matrix2.c \
		start_split.c \
		get_env.c \
		get_export.c \
		get_exit.c \
		get_cd.c \
		expanding.c \
		create_nodes.c \
		get_redir.c \
		check_start.c \
		validate_fork.c \
		tokens_subsplit.c \
		remove_quotes.c \
		heredoc_infile.c \
		error.c \
		init.c \
		check_start2.c \
		init_env.c \
		print_error.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_split.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c	 \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c


OBJ	= $(addprefix objs/,$(SRC:.c=.o))

CC	=	gcc
CFLAGS	= -Wall -Wextra -Werror

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c  -I ~/.brew/opt/readline/include -o $@ $^

all:	$(NAME)

$(NAME): $(OBJ) include/minishell.h include/get_next_line.h src/libft.h
	@echo "Compilar normal"
	@$(CC) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib -o $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf ./objs

fclean:	clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m