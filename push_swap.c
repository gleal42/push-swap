#include "push_swap.h"

int	is_input_valid(char **stack_a_args)
{
	int i;

	if (!*stack_a_args)
		return (0);
	i = 0;
	while (stack_a_args[i])
	{
		if (!is_integer(stack_a_args[i]))
			return (0);
		i++;
	}
	return (1);
}

t_list *prepare_stack_a(char **stack_a_args)
{
	int nbr;
	t_list	*head;

	if (!is_input_valid(stack_a_args))
		return(0);	
	printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
	nbr = ft_atoi(stack_a_args[0]);
	head = ft_lstnew(&nbr);
	return (head);
/* 	i = 0;
	while (stack_a_args[i])
	{
		if (i != 0)
	} */
}

void	push_swap(char **stack_a_args)
{
	t_list *a;

	a = prepare_stack_a(stack_a_args);
}

int	main(int argc, char **argv)
{
	if (argc >= 1)
		push_swap(&argv[1]);
}