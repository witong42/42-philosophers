NAME	= philo

SRCS	= srcs/main.c srcs/init.c srcs/actions.c srcs/routine.c srcs/monitoring.c srcs/ft_utils.c srcs/philo_utils.c
OBJS	= $(SRCS:%.c=%.o)

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
#CFLAGS2 = -fsanitize=thread -g
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

