SRCS	= main.c clean_data.c ft_split.c ft_strcmp.c ft_strcpy.c ft_strlen.c test_main.c lexer.c parser.c utils_tab_node.c check_node.c get_type.c utils_lc.c display_env_list.c create_env_tab.c env_var_exist.c expand_or_not.c

OBJS	= ${SRCS:.c=.o}
CC	= cc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror
NAME	= minishell

${NAME}: ${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline
all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all