NAME = philo
SRC_DIR = ./src/
SRCS = main.c
OBJS += $(addprefix $(SRC_DIR), $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I include
LDFLAGS =

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(INCLUDE)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
