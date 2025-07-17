NAME = philo
CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =	srcs/philo.c \
		srcs/philo_utils.c \
		srcs/args_check.c \
		srcs/init_data.c \
		srcs/data_utils.c \
		srcs/threads.c \
		srcs/time_func.c \
		srcs/simulation.c \
		srcs/sim_utils.c \
		srcs/monitor.c \
		srcs/clean_utils.c \

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
