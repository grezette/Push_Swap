#include "../include/push_swap.h"

static void
	psw_sort_three_args(t_plural_stacks *stack, char *str, int *len)
{
	if (stack->a->nb > stack->a->next->nb && stack->a->nb < stack->a->next->next->nb)
		psw_operation(stack, str, "sa", len);
	else if (stack->a->nb > stack->a->next->nb && stack->a->next->nb > stack->a->next->next->nb)
	{
		psw_operation(stack, str, "sa", len);
		psw_operation(stack, str, "rra", len);
	}
	else if (stack->a->nb > stack->a->next->next->nb && stack->a->next->nb < stack->a->next->next->nb)
		psw_operation(stack, str, "ra", len);
	else if (stack->a->nb < stack->a->next->next->nb && stack->a->next->nb > stack->a->next->next->nb)
	{
		psw_operation(stack, str, "sa", len);
		psw_operation(stack, str, "ra", len);
	}
	else if (stack->a->nb < stack->a->next->nb && stack->a->nb > stack->a->next->next->nb)
		psw_operation(stack, str, "rra", len);
}

static void
	psw_sort_fourth_arg(t_plural_stacks *stack, char *str, int *i)
{
	if (stack->b->nb < stack->a->nb)
		psw_operation(stack, str, "pa", i);
	else if (stack->b->nb < stack->a->next->nb)
	{
		psw_operation(stack, str, "ra", i);
		psw_operation(stack, str, "pa", i);
		psw_operation(stack, str, "rra", i);
	}
	else
	{
		if (stack->b->nb < stack->a->next->next->nb)
			psw_operation(stack, str, "rra", i);
		psw_operation(stack, str, "pa", i);
		psw_operation(stack, str, "ra", i);
		if (stack->a->nb > stack->a->next->nb)
			psw_operation(stack, str, "ra", i);
	}
}

static void
	psw_sort_fifth_in_four_particular_case(t_plural_stacks *stack, t_info *inf)
{
	if (stack->b->nb < stack->b->next->nb)
		psw_operation(stack, inf->output, "rb", &inf->i);
	if (stack->a->next->nb > stack->b->nb)
		psw_operation(stack, inf->output, "ra", &inf->i);
	else 
		psw_operation(stack, inf->output, "rra", &inf->i);
	psw_multiple_op(stack, "pa\npa\n", inf);
	if (stack->a->nb < stack->a->next->nb)
		while (stack->a->nb)
			psw_operation(stack, inf->output, "rra", &inf->i);
	else
		while (stack->a->nb)
			psw_operation(stack, inf->output, "ra", &inf->i);
}

static void
	psw_sort_two_in_three(t_plural_stacks *stack, t_info *inf, int ac)
{
	if (stack->b->nb == 0 || stack->b->next->nb == 0 ||
			stack->b->nb == ac - 1 || stack->b->next->nb == ac - 1)
	{
		if (stack->b->nb == 0 || (stack->b->nb == ac - 1 &&
					stack->b->next->nb != 0))
			psw_operation(stack, inf->output, "rb", &inf->i);
		psw_sort_fourth_arg(stack, inf->output, &inf->i);
		psw_operation(stack, inf->output, "pa", &inf->i);
		if (stack->a->nb > stack->a->next->nb)
			psw_operation(stack, inf->output, "ra", &inf->i);
	}
	else if ((stack->a->next->nb > stack->b->nb &&
				stack->a->next->nb < stack->b->next->nb) ||
			(stack->a->next->nb < stack->b->nb &&
			 stack->a->next->nb > stack->b->next->nb))
	{
		if (stack->b->nb > stack->b->next->nb)
			psw_operation(stack, inf->output, "rb", &inf->i);
		psw_multiple_op(stack, "ra\npa\nra\nra\npa\nra\nra\n", inf);
	}
	else
		psw_sort_fifth_in_four_particular_case(stack, inf);
}

int
	psw_small_algo(t_plural_stacks *stack, t_info *inf, int ac)
{
	if (ac == 3)
		psw_sort_three_args(stack, inf->output, &(inf->i));
	if (ac == 4 || ac == 5)
  	{
		if (ac == 5)
			psw_operation(stack, inf->output, "pb", &(inf->i));
		psw_operation(stack, inf->output, "pb", &(inf->i));
		psw_sort_three_args(stack, inf->output, &(inf->i));
		if (ac == 5)
			psw_sort_two_in_three(stack, inf, ac);
		else
			psw_sort_fourth_arg(stack, inf->output, &(inf->i));
  	}
  	else
		if (stack->a->nb > stack->a->next->nb)
			psw_operation(stack, inf->output, "rra", &(inf->i));
	write(1, inf->output, inf->i);
	return (0);
}
