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
		print_error.c


OBJ	= $(addprefix objs/,$(SRC:%.c=%.o))

CC	=	gcc
CFLAGS	= -Wall -Wextra -Werror

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c -I ~/.brew/opt/readline/include -o $@ $^

all:	$(NAME)

$(NAME): $(OBJ) include/minishell.h compile_libft
	@echo "Compilar normal"
	@$(CC) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib libft/libft.a -o $(NAME)

compile_libft:
	@make -C ./libft
	@make bonus -C ./libft

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