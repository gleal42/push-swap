#include "push_swap.h"

/* void prepare_stack_b(char **stack_a_args)
{

} */

t_list *prepare_stack_a(char **stack_a_args)
{
	int	i;

	i = 0;
	while (stack_a_args[i])
	{
		
	}
}

void	push_swap(char **stack_a_args)
{
	t_list *a;
	// t_list *b;

	a = prepare_stack_a(stack_a_args);
	// b = prepare_stack_b(stack_a_args);
}

int	main(int argc, char **argv)
{
	if (argc)
		push_swap(argv);
}