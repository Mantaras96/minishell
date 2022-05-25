# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albertmantaras <albertmantaras@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 00:26:11 by albertmanta       #+#    #+#              #
#    Updated: 2022/05/26 00:48:32 by albertmanta      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRC	=	main.c \
		../42_get_next_line/get_next_line_utils.c \
		../42_get_next_line/get_next_line.c \


OBJ	= $(addprefix objs/,$(SRC:.c=.o))

CC	=	gcc
CFLAGS	= -Wall -Wextra -Werror

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^

all:	$(NAME)

$(NAME): $(OBJ) include/minishell.h
	@make -C ./ft_printf
	@$(CC) $(OBJ) ft_printf/libftprintf.a -o $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf ./objs

fclean:	clean
	@make fclean -C ./ft_printf
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean