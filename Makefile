SRC =	mandatory/main.c \
		mandatory/utils.c \
		mandatory/args.c \
		mandatory/philo_list.c \
		mandatory/philo_routine.c \
		mandatory/print.c \
		mandatory/threads.c \
		mandatory/time.c

SRC_BONUS =	bonus/main.c \
			bonus/utils.c \
			bonus/args.c \
			bonus/philo_list.c \
			bonus/philo_routine.c \
			bonus/print.c \
			bonus/threads.c \
			bonus/time.c

OBJS = ${SRC:.c=.o}
OBJS_BONUS = ${SRC_BONUS:.c=.o}

FLAGS = -Wall -Werror -Wextra -pthread

CC = gcc

NAME = philo


ifdef INCLUDE_BONUSES
OBJS_LIST = $(OBJS_BONUS)
else
OBJS_LIST = $(OBJS)
endif

${NAME} : ${OBJS_LIST}
		${CC} ${FLAGS} ${OBJS_LIST} -o ${NAME}

bonus:		
	$(MAKE) INCLUDE_BONUSES=1

all:		$(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re bonus