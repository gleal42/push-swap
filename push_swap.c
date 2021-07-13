#include "push_swap.h"

void	prepare_stack_a(t_stack **a, char **stack_a_args)
{
	t_stack	*next_nbr;
	int	nbr;
	int i;

	i = 0;
	while (stack_a_args[i])
	{
		nbr = ft_atoi(stack_a_args[i]);
		if (is_nbr_in_stack(nbr, *a))
		{
			printf("Error\n");
			exit(EXIT_FAILURE);
		}
		next_nbr = stacknew(nbr);
		if (!next_nbr)
			exit(EXIT_FAILURE);
		stackadd_back(a, next_nbr);
		i++;
	}
}

int		ft_nbr_strs(char **strs)
{
	int i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i])
		i++;
	return (i);
}

void	get_stack_info(t_stack	**a, int n)
{
	t_stack *first;
	t_stack *next_min;
	int i;

	i = 1;
	first = (*a);
	while (i <= n)
	{
		*a = first;
		next_min = 0;
		while (*a)
		{
			if (!(*a)->pos &&
				(next_min == 0 || ((*a)->nbr < next_min->nbr)))
					next_min = *a;
			*a = (*a)->next;
		}
		*a = next_min;
		(*a)->pos = i;
		i++;
	}
	*a = first;
}


void	push_swap(char **stack_a_args)
{
	t_stack *a;
	t_stack *b;
	int max_len;
	int n;

	a = NULL;
	b = NULL;
	if (!is_input_integer(stack_a_args))
		return ;
	prepare_stack_a(&a, stack_a_args);
	n = ft_nbr_strs(stack_a_args);
	get_stack_info(&a, n);
	max_len = biggest_str_len(stack_a_args);
	print_both_stacks(a, b, max_len);
	ft_sort_stacks(&a, &b, max_len, n);
}

int	main(int argc, char **argv)
{
	if (argc >= 1)
		push_swap(&argv[1]);
}