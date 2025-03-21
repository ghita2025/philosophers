NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=undefined -fsanitize=thread

SRC = actions.c init.c monitor.c philo.c simulation.c utils.c validation.c

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
