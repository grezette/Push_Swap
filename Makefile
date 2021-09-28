NAME 	= push_swap

SRCS 	=	srcs/push_swap.c \
			srcs/push_swap_utils.c \
			srcs/psw_pars_args.c \
			srcs/psw_small_algo.c \
			srcs/psw_operations.c

OBJS 	= $(SRCS:.c=.o)

RM		= 	rm -rf

CC 		= gcc

FLAGS 	= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
				$(CC) $(FLAGS) $^ -o $@

%.o:		%.c
				$(CC) $(FLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.PHONY: 	clean fclean re
