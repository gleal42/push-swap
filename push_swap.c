#include "push_swap.h"

void	ft_sort_stacks(t_stack **a, t_stack **b)
{
	printf("\nOperation Time:\n");

	op_rra(a);
	printf("\nStack A after:\n");
	print_stack(*a);
	printf("\nStack B after:\n");
	print_stack(*b);
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
		next_nbr = stacknew(nbr);
		if (!next_nbr)
			exit(EXIT_FAILURE);
		stackadd_back(a, next_nbr);
		i++;
	}
}

void	push_swap(char **stack_a_args)
{
	t_stack *a;
	t_stack *b;

	if (!is_input_valid(stack_a_args))
		return ;
	prepare_stack_a(&a, stack_a_args);
	printf("Stack A before:\n");
	print_stack(a);
	printf("\nStack B before:\n");
	ft_sort_stacks(&a, &b);
}

int	main(int argc, char **argv)
{
	if (argc >= 1)
		push_swap(&argv[1]);
}