/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:54:15 by gleal             #+#    #+#             */
/*   Updated: 2022/02/14 15:20:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_all	all;
	int		n;

	all.a.head = NULL;
	all.b.head = NULL;
	if (!is_input_integer(stack_a_args))
		return ;
	prepare_stack_a(&(all.a.head), stack_a_args);
	n = nbr_strs(stack_a_args);
	add_positions(&(all.a.head), n);
	max_len = biggest_str_len(stack_a_args);
	print_both_stacks(all.a.head, all.b.head);
	ft_sort_stacks(&all, n);
	stack_clear(&(all.a.head), delete_stack);
	stack_clear(&(all.b.head), delete_stack);
	check_leaks();
	exit(EXIT_SUCCESS);
}

void	add_positions(t_elem	**a, int n)
{
	t_elem		*first;
	t_elem		*next_min;
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
