NAME = philo
SRC_DIR = src/
SRCS = main.c \
		parse_args.c \
		init.c \
		thread.c \
		thread_helper.c \
		philo.c \
		philo_helper.c \
		utils_helper.c \
		utils.c
OBJS += $(addprefix $(SRC_DIR), $(SRCS:.c=.o))

CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iinclude
LDFLAGS =

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(INCLUDE)

debug: $(OBJS)
	gcc -g -fsanitize=thread $(CFLAGS) -o $@ $(OBJS) $(INCLUDE)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME) debug

re: fclean all
