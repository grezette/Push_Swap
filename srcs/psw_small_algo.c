#include "../include/push_swap.h"

static void
	psw_sort_three_args(t_plural_stacks *stack, char *str, int *len)
{
	if (stack->a->nb > stack->a->next->nb && stack->a->nb < stack->a->next->next->nb)
		psw_operation(stack, str, "sa\n", len);
	else if (stack->a->nb > stack->a->next->nb && stack->a->next->nb > stack->a->next->next->nb)
	{
		psw_operation(stack, str, "sa\n", len);
		psw_operation(stack, str, "rra\n", len);
	}
	else if (stack->a->nb > stack->a->next->next->nb && stack->a->next->nb < stack->a->next->next->nb)
		psw_operation(stack, str, "ra\n", len);
	else if (stack->a->nb < stack->a->next->next->nb && stack->a->next->nb > stack->a->next->next->nb)
	{
		psw_operation(stack, str, "sa\n", len);
		psw_operation(stack, str, "ra\n", len);
	}
	else if (stack->a->nb < stack->a->next->nb && stack->a->nb > stack->a->next->next->nb)
		psw_operation(stack, str, "rra\n", len);
}

int
	psw_small_algo(t_plural_stacks *stack, int ac)
{
	char str[49];

	int i;

	i = 0;
	if (ac == 3)
		psw_sort_three_args(stack, str, &i);
/*		else if (ac == 4)
		{
		}
		else
		{
			write();
		}
*/		
	write(1, str, i);
	return (0);
}
