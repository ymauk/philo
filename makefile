NAME = philo
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -fsanitize=address
SRC = src/philo.c src/parsing.c src/utils.c src/routine.c src/messages.c
OBJ_DIR = obj
OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

B:= "\033[0;34m"
P:= "\033[0;35m"
R:= "\033[0;31m"
G:= "\033[0;32m"
Y:= "\033[0;33m"
DC:= "\033[0;39m"

$(NAME): $(OBJS)
	@echo $(G)"Compiling philo..."$(DC)
	@cc $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo $(Y)"philo is ready to start"$(DC)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@cc $(CFLAGS) -c $< -o $@

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo $(Y)"\nEverything is properly cleaned!\n"$(DC)

re: fclean all

.PHONY: all clean fclean re