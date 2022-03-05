/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:54:15 by gleal             #+#    #+#             */
/*   Updated: 2022/03/05 17:46:32 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	if (argc > 1)
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
	ft_sort_stacks(&all, n);
	stack_clear(&(all.a.head), delete_stack);
	stack_clear(&(all.b.head), delete_stack);
	exit(EXIT_SUCCESS);
}
