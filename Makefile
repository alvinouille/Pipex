
NAME	= pipex

SRC		=	src/error.c  src/main.c src/pipex.c src/utils.c src/utils2.c src/utils3.c src/utils4.c src/utils5.c
BONUSSRC = bonus/bonus.c bonus/error.c bonus/get_next_line.c bonus/get_next_line_utils.c bonus/utils.c bonus/utils2.c bonus/utils3.c bonus/utils4.c bonus/utils5.c bonus/pipex.c bonus/main.c

OBJS    = ${SRC:.c=.o}
BONUSOBJS = ${BONUSSRC:.c=.o}

OPTION = -I ./

CC	= cc
RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror


.c.o:
			${CC} -c ${CFLAGS} ${OPTION} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS}

all:		${NAME}

bonus:		${BONUSOBJS} 
			${CC} -o ${NAME} ${BONUSOBJS}

clean:
			${RM} ${OBJS} ${BONUSOBJS} ${DEPS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re bonus
