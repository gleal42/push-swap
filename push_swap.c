#include "push_swap.h"

void	ft_sort_stacks(t_list **a, t_list **b)
{
	(void)b;
	operation_sa(a);
	ft_print_list_long(*a);
}

void	prepare_stack_a(t_list **a, char **stack_a_args)
{
	t_list	*next_nbr;
	long long	nbr;
	int i;

	i = 0;
	while (stack_a_args[i])
	{
		nbr = ft_atoi(stack_a_args[i]);
		if (is_nbr_in_list(nbr, *a))
		{
			printf("Error\n");
			exit(EXIT_FAILURE);
		}
		next_nbr = ft_lstnew((void *)nbr);
		if (!next_nbr)
			exit(EXIT_FAILURE);
		ft_lstadd_back(a, next_nbr);
		i++;
	}
}

void	push_swap(char **stack_a_args)
{
	t_list *a;
	t_list *b;

	if (!is_input_valid(stack_a_args))
		return ;
	prepare_stack_a(&a, stack_a_args);
	ft_print_list_long(a);
	ft_sort_stacks(&a, &b);
}

int	main(int argc, char **argv)
{
	if (argc >= 1)
		push_swap(&argv[1]);
}