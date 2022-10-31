
NAME = philo
SRC = ./philosophers.c \
 ./config/config.c \
 ./config/config_utils.c \
 ./config/libft_utils.c \
 ./dining/dining.c \
 ./state_manager/time_utils.c \
 ./state_manager/state_utils.c \
 ./state_manager/monitor.c \
 ./state_manager/monitor_utils.c
HEADER = ./philo.h
OBJ = $(SRC:.c=.o)


FLAGS = -g -pthread -Wall -Werror -Wextra
all: $(NAME)

$(NAME): $(HEADER) $(OBJ)
	@gcc $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\n\033[92m $@ built 🍝\033[0m\n"

%.o : %.c $(HEADER)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\n\033[36m object files removed 👋\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@echo "\n\033[36m executables removed 👋\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
