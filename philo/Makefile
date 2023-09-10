NAME			=	philo
CC				=	cc
FLAGS			=	-Wall -Werror -Wextra #-fsanitize=thread 
RM				=	rm -rf
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
NC				=	\033[0m

SRC				=	srcs/main.c \
					srcs/checkers.c \
					srcs/table_utils.c \
					srcs/philo.c \
					srcs/time.c \
					srcs/err.c \
					srcs/routine.c \
					srcs/choose_fork.c \
					srcs/death_routine.c \
					srcs/ft_strlen.c \
					srcs/messages.c \
					srcs/ft_putstr_fd.c \
					srcs/ft_putchar_fd.c \
					srcs/ft_putnbr_fd.c \
					srcs/ft_atoi.c

OBJS_DIR		=	.OBJS/
OBJS			=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

HEADER_DIR		=	headers/
HEADER_FILE		=	headers/philosophers.h \
					headers/struct.h

$(NAME):			$(OBJS_DIR) Makefile $(HEADER_FILE) $(OBJS)
					@$(CC) $(FLAGS) -g -I $(HEADER_DIR) $(OBJS) -lpthread -lrt -o $@
					@echo "\33[2K\r$(GREEN)Philosophers compiled :D$(NC)"
					
$(OBJS_DIR)%.o:	%.c $(HEADER_FILE)
					@$(CC) $(FLAGS) -g -I $(HEADER_DIR) -c $< -o $@
					@echo -n "\33[2K\r$(YELLOW)Compiled $<"

$(OBJS_DIR):
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)srcs

all:				$(NAME)

norm:
					@norminette $(SRC) $(HEADER_DIR) | awk '$$NF!="OK!" {print "$(RED)" $$0 "$(NC)"}'
					
clean:
				@echo "$(RED)Deleting $(NAME) object...\n"
				@$(RM) $(OBJS_DIR)
				@echo "$(GREEN)Done\n"

fclean:			clean
				@echo "$(RED)Deleting $(NAME) executable..."
				@rm -f $(NAME)
				@echo "$(GREEN)Done\n"

re:				fclean all

.PHONY:			all clean fclean re
