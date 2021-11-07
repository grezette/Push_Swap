#include "../include/push_swap.h"

int
	prs_atoi(char *av, int *nb)
{
	int			minus;
	long int	atoi;

	atoi = 0;
	minus = 1;
	if (*av == '-')
	{
		minus = -1;
		av++;
	}
	while ('0' <= *av && *av <= '9')
	{
		atoi = atoi * 10 + *av++ - '0';
		if (atoi - 1 == INT_MAX && minus == -1 && !*av)
			break ;
		else if (atoi > INT_MAX)
			return (-1);
	}
	if (*av)
		return (-1);
	*nb = atoi * minus;
	return (0);
}

int
	check_if_double_arg(t_stack *stack, int nb)
{
	if (!stack->next)
		return (0);
	while (stack->next)
	{
		if (stack->nb == nb)
			return (-1);
		stack = stack->next;
	}
	return (0);
}

static void
	psw_regular_algo(t_plural_stacks *stack, t_info *inf, int ac)
{
	int	right_shift;
	int	max_bits;
	int	tmp;

	right_shift = -1;
	max_bits = 3;
	while (ac >> max_bits)
		max_bits++;
	while (++right_shift <= max_bits - 1)
	{
		tmp = ac;
		while (--tmp)
		{
			if (((stack->a->nb >> right_shift) & 1))
				psw_operation(stack, inf->output, "ra", &inf->i);
			else
				psw_operation(stack, inf->output, "pb", &inf->i);
		}
		while (stack->b)
			psw_operation(stack, inf->output, "pa", &inf->i);
	}
	write(1, inf->output, inf->i);
}

int
	main(int ac, char **av)
{
	t_plural_stacks	stack;
	t_info			inf;

	if (init_var(&stack, &inf))
		return (write(1, "Error\n", 6));
	if (psw_pars_args(ac, av, &stack.a))
		return (write(1, "Error\n", 6) + free_memory(stack));
	if (!psw_a_is_sorted(stack.a))
		return (free_memory(stack));
	if (ac <= 6)
		psw_small_algo(&stack, &inf, ac - 1);
	else
		psw_regular_algo(&stack, &inf, ac);
	free_memory(stack);
	return (0);
}
