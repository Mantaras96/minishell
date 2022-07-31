NAME	=	minishell

SRC	=	main.c \
		../42_get_next_line/get_next_line_utils.c \
		../42_get_next_line/get_next_line.c \
		get_pwd.c \
		print_flowers.c \
		get_echo.c \
		parsing.c \
		tokens.c \
		start_minishell.c \
		utils_matrix.c \
		get_env.c \
		get_export.c \
		get_exit.c \
		get_cd.c \
		expanding.c \
		get_path.c \
		create_nodes.c \
		get_redir.c \
		check_start.c \
		validate_fork.c \
		tokens_subsplit.c \
		remove_quotes.c \
		heredoc_infile.c \
		error.c


OBJ	= $(addprefix objs/,$(SRC:.c=.o))

CC	=	gcc
CFLAGS	= -Wall -Wextra -Werror

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c -I ~/.brew/opt/readline/include -o $@ $^

all:	$(NAME)

$(NAME): $(OBJ) include/minishell.h
	@make -C ./ft_printf
	@$(CC) $(OBJ) -lreadline -L ~/.brew/opt/readline/lib ft_printf/libftprintf.a -o $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf ./objs

fclean:	clean
	@make fclean -C ./ft_printf
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean