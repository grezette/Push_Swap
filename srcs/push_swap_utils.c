#include "../include/push_swap.h"

void
	psw_multiple_op(t_plural_stacks *stack, char *str, t_info *inf)
{
	int		j;
	int		k;
	char	op[4];

	j = -1;
	k = 0;
	while (str[++j])
	{
		while (str[j] && str[j] != '\n')
			op[k++] = str[j++];
		op[k] = 0;
		psw_operation(stack, inf->output, op, &(inf->i));
		k = 0;
	}
}

int
	free_memory(t_plural_stacks stack)
{
	t_stack	*tmp;

	while (stack.a)
	{
		tmp = stack.a;
		stack.a = stack.a->next;
		free(tmp);
	}
	while (stack.b)
	{
		tmp = stack.b;
		stack.b = stack.b->next;
		free(tmp);
	}
	return (0);
}

t_stack
	*init_elem(int nb)
{
	t_stack	*new_elem;

	new_elem = (t_stack *)malloc(sizeof(t_stack *));
	if (new_elem)
	{
		new_elem->nb = nb;
		new_elem->next = NULL;
	}
	return (new_elem);
}

int
	init_var(t_plural_stacks *stack, t_info *inf)
{
	stack->a = init_elem(0);
	if (!stack->a)
		return (-1);
	stack->b = NULL;
	inf->i = 0;
	return (0);
}

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
