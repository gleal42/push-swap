#include "push_swap.h"

int	main(int argc, char **argv)
{
	if (argc >= 1)
		push_swap(&argv[1]);
}

/*
** Validates input, creates a stack and sorts it using algorithm
** @param:	- [char **] numbers to be sorted
**
** Line-by-line comments:
** @8	validation to see if all inputs are valid numbers
** @10	Validates duplicate numbers
** 		duplicate validation done inside
** @12	Might be useful to improve algorithm (sort/parameters.c)
*/

void	push_swap(char **stack_a_args)
{
	t_stack	*a;
	t_stack	*b;
	int		max_len;
	int		n;

	a = NULL;
	b = NULL;
	if (!is_input_integer(stack_a_args))
		return ;
	prepare_stack_a(&a, stack_a_args);
	n = nbr_strs(stack_a_args);
	add_positions(&a, n);
	max_len = biggest_str_len(stack_a_args);
	print_both_stacks(a, b, max_len);
	ft_sort_stacks(&a, &b, max_len, n);
	stacks_clear(&a, delete_stack);
	check_leaks();
	exit(EXIT_SUCCESS);
}

void	add_positions(t_stack	**a, int n)
{
	t_stack		*first;
	t_stack		*next_min;
	int			i;

	i = 1;
	first = (*a);
	while (i <= n)
	{
		*a = first;
		next_min = 0;
		while (*a)
		{
			if (! (*a)->pos
				&& (next_min == 0 || ((*a)->nbr < next_min->nbr)))
				next_min = *a;
			*a = (*a)->next;
		}
		*a = next_min;
		(*a)->pos = i;
		i++;
	}
	*a = first;
}
