SRCS	= main.c clean_data.c ft_split.c ft_strcmp.c ft_strlen.c 

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

re:		fclean al