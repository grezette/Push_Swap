#include "../include/push_swap.h"

void	visualizer(t_plural_stacks *stack)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;

	tmp_a = stack->a;
	tmp_b = stack->b;
	getc(stdin);
	while (tmp_a || tmp_b)
	{
		if (tmp_a)
		{	
			printf("%5d", tmp_a->nb);
			printf("|");
			tmp_a = tmp_a->next;
		}
		if (tmp_b)
		{
			printf("%5d", tmp_b->nb);
			tmp_b = tmp_b->next;
		}
		printf("\n");
	}
	printf("\n");
}

static void
	psw_regular_algo(t_plural_stacks *stack, t_info *inf, int ac)
{
	int right_shift;
	int	max_bits;
	int nb;
	int tmp;

	right_shift = -1;
	max_bits = 3;
	tmp = 0;
	nb = 0;
	while (ac >> max_bits)
		max_bits++;
	while (right_shift <= max_bits + 1)
	{
		tmp = ac;
		while (--tmp)
		{
			// visualizer(stack);
			nb = stack->a->nb;
			if (((nb >> right_shift)&1))
			{
				psw_operation(stack, inf->output, "ra", &inf->i);
				write(1, "ra\n", 3);
			}
			else
			{
				psw_operation(stack, inf->output, "pb", &inf->i);
				write(1, "pb\n", 3);
			}
		}
		while (stack->b)
		{
			psw_operation(stack, inf->output, "pa", &inf->i);
			write(1, "pa\n", 3);
			// visualizer(stack);
		}
		right_shift++;
	}
	// write(1, inf->output, inf->i);
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
