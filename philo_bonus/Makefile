NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = actions_bonus.c init_bonus.c monitor_bonus.c philo_bonus.c simulation_bonus.c utils_bonus.c validation_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY:
