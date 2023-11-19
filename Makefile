DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.SILENT:
NAME = philo
CFLAGS = -pthread -Wall -Wextra -Werror 
CC = cc

SRCS = philosophers.c ./utils/ft_isdigit.c ./utils/ft_atoi.c ./utils/ft_error.c garbage_collector.c \
		./utils/time.c actions.c
OBJS = $(SRCS:.c=.o)



$(NAME): $(OBJS) 
	cc  $(SRCS) -o $(NAME) $(CFLAGS)
	echo "$(GREEN)Philosophers Compiled$(DEF_COLOR)"

all: $(NAME)



clean:
	rm -f $(OBJS)
	echo "$(RED)Object Files are deleted$(DEF_COLOR)"

fclean: clean
	rm -rf $(NAME)
	echo "Everything is clean"

re: fclean all

.PHONY: all clean fclean re