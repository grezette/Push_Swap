#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef	struct	s_stack
{
	int			nb;
	struct		s_stack *next;
}				t_stack;

typedef struct	s_plural_stacks
{
	t_stack		*a;
	t_stack		*b;
}				t_plural_stacks;

typedef struct	s_info
{
	int			i;
	int			size;
	int			min_arg;
	int			max_arg;
	char		output[4096];
}				t_info;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int		psw_small_algo(t_plural_stacks *stack, t_info *inf);
int		psw_a_is_sorted(t_stack *stack);
void	psw_operation(t_plural_stacks *stack, char *str, char *op, int *len);
void	psw_multiple_op(t_plural_stacks *stack, char *str, t_info *inf);

#endif
