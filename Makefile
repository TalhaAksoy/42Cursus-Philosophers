DARKGRAY=\033[1;30m
RED=\033[0;31m
LIGHTRED=\033[1;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
LIGHTPURPLE=\033[1;35m
CYAN=\033[0;36m
WHITE=\033[1;37m
SET=\033[0m

SRCS	=	philoshophers.c ft_philo.c utils_philo.c ft_check_args.c \
			ft_check_dead.c ft_controller.c ft_init.c ft_locks.c
RM		=	@rm -f
GCC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
NAME 	=	philo

FLAGS_DATARACE	=	-fsanitize=thread -g
FLAGS_MEMORY	=	-fsanitize=address -g

all: $(NAME) $(SRCS)

$(NAME): $(SRCS)
	@$(GCC) $(FLAGS) $(SRCS) -o $(NAME)

data_race: $(SRCS)
	@$(GCC) $(FLAGS_DATARACE) $(SRCS) -o philo_thread

memory_check: $(SRCS)
	@$(GCC) $(FLAGS_MEMORY) $(SRCS) -o philo_memory

clean:
	$(RM) philo

fclean:	clean
	$(RM) philo_thread
	$(RM) -r philo_thread.dSYM
	$(RM) philo_memory
	$(RM) -r philo_memory.dSYM
	@echo "$(BLUE)cleaning 100%$(SET)"
	@sleep 1
	@clear

re:	fclean $(NAME)

.PHONY:	clean fclean re