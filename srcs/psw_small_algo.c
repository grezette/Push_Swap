#include "../include/push_swap.h"

/* 
   	Idées de fonction:
	- Fonction qui appel en boucle psw_oper via une string:
		while (str[++i])
		{
			while (str[i] != '\n')
				tmp_str[j++] = str[i++];
			tmp_str[j] = 0;
			i -= j;
			j = 0;
			psw_operation(stack, str, tmp_str, i)
		}
	
	- Fonction qui ajoute une string apres une autre
		(genre un strjoin mais pour les opération)
*/

void
	psw_multiple_op(t_plural_stacks *stack, char *str, t_info *inf)
{
	int j;
	int k;
	char op[4];

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

void
	psw_sort_two_in_three(t_plural_stacks *stack, char *str, int *i, t_info *inf)
{
	if (inf->min_arg == stack->b->nb || inf->min_arg == stack->b->next->nb ||
			inf->max_arg == stack->b->nb || inf->max_arg == stack->b->next->nb)
	{
		if (inf->min_arg == stack->b->nb || (inf->max_arg == stack->b->nb &&
					inf->min_arg != stack->b->next->nb))
			psw_operation(stack, str, "rb", i);
		psw_sort_fourth_arg(stack, str, i);
		psw_operation(stack, str, "pa", i);
		if (stack->a->nb > stack->a->next->nb)
			psw_operation(stack, str, "ra", i);
	}
	else if ((stack->a->next->nb > stack->b->nb && stack->a->next->nb < stack->b->next->nb) || (stack->a->next->nb < stack->b->nb && stack->a->next->nb > stack->b->next->nb))
	{
		if (stack->b->nb > stack->b->next->nb)
			psw_operation(stack, str, "rb", i);
		psw_multiple_op(stack, "ra\npa\nra\nra\npa\nra\nra\n", inf);
	}
	else
	{
		if (stack->b->nb < stack->b->next->nb)
			psw_operation(stack, str, "rb", i);
		if (stack->a->next->nb > stack->b->nb)
			psw_operation(stack, str, "ra", i);
		else 
			psw_operation(stack, str, "rra", i);
		psw_multiple_op(stack, "pa\npa\n", inf);
		if (stack->a->nb < stack->a->next->nb)
			psw_operation(stack, str, "rra", i);
		else
			psw_operation(stack, str, "ra", i);
	}
}

int
	psw_small_algo(t_plural_stacks *stack, t_info *inf)
{
	if (inf->size == 3)
		psw_sort_three_args(stack, inf->output, &(inf->i));
	else if (inf->size == 4 || inf->size == 5)
  	{
		if (inf->size == 5)
			psw_operation(stack, inf->output, "pb", &(inf->i));
		psw_operation(stack, inf->output, "pb", &(inf->i));
		psw_sort_three_args(stack, inf->output, &(inf->i));
		if (inf->size == 5)
			psw_sort_two_in_three(stack, inf->output, &(inf->i), inf);
		else
			psw_sort_fourth_arg(stack, inf->output, &(inf->i));
  	}
  	else
		if (stack->a->nb > stack->a->next->nb)
			psw_operation(stack, inf->output, "rra", &(inf->i));
	write(1, inf->output, inf->i);
	return (0);
}
