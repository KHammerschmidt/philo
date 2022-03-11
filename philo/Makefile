NAME 		=	philo

CC 			=	gcc
CFLAGS 		=	-Wall -Werror -Wextra -pthread -g -fsanitize=thread
# -fsanitize=thread -g

SRC_DIR		=	./src/
OBJ_DIR		=	./obj/

SRC_LIST	 =	main.c			\
				parsing.c		\
				init.c			\
				philo.c			\
				eating.c		\
				sleep_think.c	\
				print_log.c		\
				time.c			\
				thread_join.c	\
				reaper.c		\
				stuffed.c		\
				libft_utils.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJ			=	$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_LIST)))

INCLUDES	=	./header/philo.h

# **************************************************************************** #
#									RULES									   #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
