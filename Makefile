# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amantara <amantara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 00:26:11 by albertmanta       #+#    #+#              #
#    Updated: 2022/05/27 17:04:11 by amantara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRC	=	main.c \
		../42_get_next_line/get_next_line_utils.c \
		../42_get_next_line/get_next_line.c \
		get_pwd.c


OBJ	= $(addprefix objs/,$(SRC:.c=.o))

CC	=	gcc
CFLAGS	= -Wall -Wextra -Werror

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -I ~/.brew/opt/readline/include -o $@ $^

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