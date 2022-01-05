SRC =	main.c \
		utils.c \
		args.c \
		philo_list.c \
		philo_routine.c \
		print.c \
		threads.c \
		time.c


OBJS = ${SRC:.c=.o}

FLAGS = -Wall -Werror -Wextra -pthread

CC = gcc

NAME = philo

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

${NAME} : ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME}

all:		$(NAME)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re bonus