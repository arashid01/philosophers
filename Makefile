NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRC_PATH = srcs/
OBJ_PATH = objs/

SRC =	main.c \
		ft_atoi.c \
		args_check.c 

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))


all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re