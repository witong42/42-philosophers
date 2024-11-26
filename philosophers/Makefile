NAME	= philosophers

SRCS	= philo/philo.c philo/init.c philo/routine.c philo/action.c philo/utils_ft.c philo/utils_philo.c

OBJS	= $(SRCS:%.c=%.o)

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

