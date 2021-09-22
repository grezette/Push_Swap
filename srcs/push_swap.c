#include "../include/push_swap.h"

void	print_args(t_stack *stack)
{
	while (stack)
	{
		printf("%d\n", stack->nb);
		stack = stack->next;
	}
}

int
	free_memory(t_plural_stacks stack)
{
	t_stack *tmp;

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
	t_stack *new_elem;

	new_elem = (t_stack *)malloc(sizeof(t_stack *));
	if (new_elem)
		new_elem->nb = nb;
	return (new_elem);
}

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
		if (atoi -1 == INT_MAX  && minus == -1 && !*av)
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

int
	pars_arg(int ac, char **av, t_stack **a)
{
	t_stack *tmp;

	tmp = *a;
	if (ac < 1)
		return (-1);
	while (--ac)
	{
		if (prs_atoi(*(++av), &(tmp->nb)))
			return (-1);
		if (check_if_double_arg(*a, tmp->nb))
			return (-1);
		if (ac - 1)
		{
			tmp->next = init_elem(0);
			if (!tmp->next)
				return (-1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int
	main (int ac, char **av)
{
	t_plural_stacks stack;

	stack.a = init_elem(0);
	if (!stack.a)
		return (write(1, "Error\n", 6));
	stack.b = NULL;
	if (pars_arg(ac, av, &stack.a))
		return (write(1, "Error\n", 6) + free_memory(stack));
	if (ac <= 6)
		psw_small_algo(&stack, ac - 1);
	print_args(stack.a);
	free_memory(stack);
	return (0);
}
