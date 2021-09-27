#include "../include/push_swap.h"

int
	psw_a_is_sorted(t_stack *stack)
{
	if (!stack->next)
		return (0);
	while (stack->next)
	{
		if (stack->nb > stack->next->nb)
			return (-1);
		stack = stack->next;
	}
	return (0);
}
