#include "../include/push_swap.h"

static t_stack
	*ft_lstlast(t_stack *lst)
{
	if (!(lst))
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void
	add_op_to_str(char *op, char *str, int *len)
{
	int i;

	i = -1;
	if (*len > 4093)
	{
		// write(1, str, *len + 1);
		*len = 0;
	}
	while (op[++i])
		str[(*len)++] = op[i];
	str[(*len)++] = '\n';
	str[(*len)] = 0;
}

static void
	generic_operation(t_stack **ptr_1, t_stack **ptr_2, t_stack **ptr_3, int bol)
{
	t_stack *tmp;

	tmp = *ptr_1;
	if (bol)
	{
		while (tmp->next->next)
			tmp = tmp->next;
		(*ptr_2)->next = *ptr_1;
		tmp->next = NULL;
		*ptr_1 = *ptr_2;
	}
	else
	{
		*ptr_1 = tmp->next;
		if (ptr_2)
			tmp->next = *ptr_2;
		else
			tmp->next = NULL;
		(*ptr_3) = tmp;
	}
}

static void
	psw_operation_2(t_plural_stacks *stack, char *op,
			t_stack *last_tmp_a, t_stack *last_tmp_b)
{
	if (op[0] == 'r' && op[1] == 'a')
		generic_operation(&(stack->a), NULL, &(last_tmp_a)->next, 0);
	else if (op[0] == 'r' && op[1] == 'b')
		generic_operation(&(stack->b), NULL, &(last_tmp_b)->next, 0);
	else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'a')
		generic_operation(&(stack->a), &(last_tmp_a), NULL, 1);
	else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'b')
		generic_operation(&(stack->b), &(last_tmp_b), NULL, 1);
	else if (op[0] == 'r' && op[1] == 'r' && op[2] == 'r')
	{
		generic_operation(&(stack->a), &(last_tmp_a), NULL, 1);
		generic_operation(&(stack->b), &(last_tmp_b), NULL, 1);
	}
	else if (op[0] == 'r' && op[1] == 'r')
	{
		generic_operation(&(stack->a), NULL, &(last_tmp_a)->next, 0);
		generic_operation(&(stack->b), NULL, &(last_tmp_b)->next, 0);
	}
}

void
	psw_operation(t_plural_stacks *stack, char *str, char *op, int *len)
{
	t_stack *last_tmp_a;
	t_stack *last_tmp_b;

	add_op_to_str(op, str, len);
	last_tmp_a = ft_lstlast(stack->a);
	last_tmp_b = ft_lstlast(stack->b);
	if (op[0] == 's' && op[1] == 'a')
		generic_operation(&(stack->a), &(stack->a->next->next),
				&(stack->a->next->next), 0);
	else if (op[0] == 's' && op[1] == 'b')
		generic_operation(&(stack->b), &(stack->b->next->next),
				&(stack->b->next->next), 0);
	else if (op[0] == 's' && op[1] == 's')
	{
		generic_operation(&(stack->a), &(stack->a->next->next),
				&(stack->a->next->next), 0);
		generic_operation(&(stack->b), &(stack->b->next->next),
				&(stack->b->next->next), 0);
	}
	else if (op[0] == 'p' && op[1] == 'a')
		generic_operation(&(stack->b), &(stack->a), &(stack->a), 0);
	else if (op[0] == 'p' && op[1] == 'b')
		generic_operation(&(stack->a), &(stack->b), &(stack->b), 0);
	psw_operation_2(stack, op, last_tmp_a, last_tmp_b);
}
