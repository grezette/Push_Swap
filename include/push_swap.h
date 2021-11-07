#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stack
{
	int				nb;
	struct s_stack	*next;
}				t_stack;

typedef struct s_plural_stacks
{
	t_stack		*a;
	t_stack		*b;
}				t_plural_stacks;

typedef struct s_info
{
	int			i;
	char		output[4096];
}				t_info;

int		psw_pars_args(int ac, char **av, t_stack **a);
int		prs_atoi(char *av, int *nb);
int		check_if_double_arg(t_stack *stack, int nb);
int		init_var(t_plural_stacks *stack, t_info *inf);
int		free_memory(t_plural_stacks stack);
int		psw_a_is_sorted(t_stack *stack);
int		psw_small_algo(t_plural_stacks *stack, t_info *inf, int ac);
void	psw_multiple_op(t_plural_stacks *stack, char *str, t_info *inf);
void	psw_operation(t_plural_stacks *stack, char *str, char *op, int *len);
t_stack	*init_elem(int nb);

#endif
