#include "../include/push_swap.h"

static void
	psw_regular_algo(t_plural_stacks *stack, t_info *inf, int ac)
{
	int right_shift;
	int	max_bits;
	int tmp;

	right_shift = -1;
	max_bits = 3;
	while (ac >> max_bits)
		max_bits++;
	while (++right_shift <= max_bits - 1)
	{
		tmp = ac;
		while (--tmp)
		{
			if (((stack->a->nb >> right_shift)&1))
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
	main (int ac, char **av)
{
	t_plural_stacks stack;
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
