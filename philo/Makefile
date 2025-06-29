NAME = philo
CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =	srcs/philo.c \
		srcs/philo_utils.c \

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
		${CC} ${OBJS} ${CFLAGS} -o ${NAME}

clean: 
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re