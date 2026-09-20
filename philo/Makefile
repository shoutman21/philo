NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I.

SRC_PATH = src

SRCS = main.c parsing.c utils.c init.c print.c routine.c threads.c monitor.c \
	forks.c

OBJS = $(addprefix $(SRC_PATH)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
