# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albertmantaras <albertmantaras@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 00:26:11 by albertmanta       #+#    #+#              #
#    Updated: 2022/05/22 00:26:45 by albertmanta      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	minishell

SRC	=	main.c \

OBJ	= $(addprefix objs/,$(SRC:.c=.o))

CC	=	gcc
CFLAGS	= -Wall -Wextra -Werror

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^

all:	$(NAME)

$(NAME): $(OBJ) include/minishell.h
	@make -C libft
	@$(CC) $(OBJ) libft/libft.a -o $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf ./objs

fclean:	clean
	@make fclean -C libft
	@rm -f $(NAME)

re:	fclean all

.PHONY: all re clean fclean