#include "push_swap.h"

void	ft_sort_stacks(t_stack **a, t_stack **b)
{
	// op_sa(a);
	op_pa(a, b);
	op_pb(a, b);
	printf("Stack A after:\n");
	ft_print_stack(*a);
	printf("Stack B after:\n");
	ft_print_stack(*b);
}

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
		next_nbr = ft_stacknew(nbr);
		if (!next_nbr)
			exit(EXIT_FAILURE);
		ft_stackadd_back(a, next_nbr);
		i++;
	}
}

void	push_swap(char **stack_a_args)
{
	t_stack *a;
	t_stack *b;

	a = NULL;
	b = NULL;
	if (!is_input_valid(stack_a_args))
		return ;
	prepare_stack_a(&a, stack_a_args);
	printf("Stack A before:\n");
	ft_print_stack(a);
	printf("Stack B before:\n");
	ft_sort_stacks(&a, &b);
}

int	main(int argc, char **argv)
{
	if (argc >= 1)
		push_swap(&argv[1]);
}