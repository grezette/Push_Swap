#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef	struct	s_stack
{
	int		nb;
	struct	s_stack *next;
}				t_stack;

typedef struct s_plural_stacks
{
	t_stack	*a;
	t_stack *b;
}				t_plural_stacks;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int		psw_small_algo(t_plural_stacks *stack, int ac);
void	psw_operation(t_plural_stacks *stack, char *str, char *op, int *len);

#endif
