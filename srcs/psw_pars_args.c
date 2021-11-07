#include "../include/push_swap.h"

static void
	pars_sort_tab(int *tab, int ac)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	while (++i < ac - 1)
	{
		j = -1;
		while (++j < ac - 1)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}

static int
	pars_binary_search(int *tab, int ac, int to_found)
{
	int	i;
	int	minus;
	int	range;

	minus = 0;
	range = 2;
	i = ac / range;
	while (i <= ac && i >= 0)
	{
		if (ac / range == 0)
			ac *= 2;
		i += ac / range * minus;
		if (tab[i] == to_found)
			return (i);
		else if (to_found < tab[i])
			minus = -1;
		else
			minus = 1;
		range *= 2;
	}
	return (1);
}

static void
	pars_change_args_in_list(t_stack **a, int *tab, int ac)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = *a;
	while (i < ac)
	{
		tmp->nb = pars_binary_search(tab, ac, tmp->nb);
		tmp = tmp->next;
		i++;
	}
}

static int
	pars_simplify_list(t_stack **a, int ac)
{
	t_stack	*tmp;
	int		*tab;
	int		i;

	tmp = *a;
	i = -1;
	tab = (int *)malloc(sizeof(*tab) * ac + 1);
	if (!tab)
		return (-1);
	while (++i < ac)
	{
		tab[i] = tmp->nb;
		tmp = tmp->next;
	}
	pars_sort_tab(tab, ac);
	pars_change_args_in_list(a, tab, ac);
	free(tab);
	return (0);
}

int
	psw_pars_args(int ac, char **av, t_stack **a)
{
	t_stack	*tmp;

	tmp = *a;
	if (ac < 1)
		return (0);
	while (av[1])
	{
		if (prs_atoi(*(++av), &(tmp->nb)) || check_if_double_arg(*a, tmp->nb))
			return (-1);
		if (av[1])
		{
			tmp->next = init_elem(0);
			if (!tmp->next)
				return (-1);
			tmp = tmp->next;
		}
	}
	if (pars_simplify_list(a, ac - 1))
		return (-1);
	return (0);
}
