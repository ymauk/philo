NAME = philo
CFLAGS = -Wall -Wextra -Werror
SRC = src/philo
OBJS = $(SRC:.c=.o)

B:= "\033[0;34m"
P:= "\033[0;35m"
R:= "\033[0;31m"
G:= "\033[0;32m"
Y:= "\033[0;33m"
DC:= "\033[0;39m"

$(NAME): $(OBJS)
	@echo $(G)"Compiling philo..."$(DC)
	@cc $(OBJS) -o $(NAME)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo $(Y)"\nEverything is properly cleaned!\n"$(DC)

re: fclean all

.PHONY: all clean fclean re