SRCS =	src/main.c \
		src/get_next_line_utils.c \
		src/get_next_line.c \
		src/get_pwd.c \
		src/print_flowers.c \
		src/get_echo.c \
		src/parsing.c \
		src/tokens.c \
		src/utils_matrix.c \
		src/utils_matrix2.c \
		src/start_split.c \
		src/get_env.c \
		src/get_export.c \
		src/get_exit.c \
		src/get_cd.c \
		src/expanding.c \
		src/create_nodes.c \
		src/get_redir.c \
		src/check_start.c \
		src/validate_fork.c \
		src/tokens_subsplit.c \
		src/remove_quotes.c \
		src/heredoc_infile.c \
		src/error.c \
		src/init.c \
		src/check_start2.c \
		src/init_env.c \
		src/print_error.c \
		src/ft_memset.c \
		src/ft_bzero.c \
		src/ft_memcpy.c \
		src/ft_memmove.c \
		src/ft_memchr.c \
		src/ft_memcmp.c \
		src/ft_strlen.c \
		src/ft_strlcpy.c \
		src/ft_strlcat.c \
		src/ft_strchr.c \
		src/ft_strrchr.c \
		src/ft_strnstr.c \
		src/ft_strncmp.c \
		src/ft_atoi.c \
		src/ft_isalpha.c \
		src/ft_split.c \
		src/ft_isdigit.c \
		src/ft_isalnum.c \
		src/ft_isascii.c \
		src/ft_isprint.c \
		src/ft_toupper.c \
		src/ft_tolower.c \
		src/ft_calloc.c \
		src/ft_strdup.c \
		src/ft_substr.c \
		src/ft_strjoin.c \
		src/ft_strtrim.c \
		src/ft_itoa.c \
		src/ft_strmapi.c \
		src/ft_striteri.c \
		src/ft_putchar_fd.c \
		src/ft_putstr_fd.c \
		src/ft_putendl_fd.c \
		src/ft_putnbr_fd.c \
		src/ft_lstnew.c	 \
		src/ft_lstadd_front.c \
		src/ft_lstsize.c \
		src/ft_lstlast.c \
		src/ft_lstadd_back.c \
		src/ft_lstdelone.c \
		src/ft_lstclear.c \
		src/ft_lstiter.c \
		src/ft_lstmap.c

OBJS = ${SRCS:.c=.o}
NAME = minishell

HEADER = include/minishell.h
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
.c.o:
	${CC} ${CFLAGS} $(COMFILE_FLAGS) -I ${HEADER} -c $< -o ${<:.c=.o}
	
${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} $(COMFILE_FLAGS) ${LINKING_FLAGS} ${OBJS} -o ${NAME}
all:		${NAME}

test:		${OBJS} ${HEADER}
			${CC}  ${CFLAGS} $(COMFILE_FLAGS) ${LINKING_FLAGS} ${OBJS} -o ${NAME}	&& ./minishell
clean: 		
			${RM} ${OBJS}
fclean: 	clean
			${RM} ${NAME}
			${RM} bonus
re:			fclean all
.PHONY: all clean fclean re