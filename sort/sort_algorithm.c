/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:45:17 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 16:28:55 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*
** Checks if numbers are already in ascending order. 
** Sorts them in case they are not
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** Line-by-line comments:
** @4	if they already in ascending order just rotate them
** @7	if they are not in ascending order
**		sort them using the other commands
*/

void	ft_sort_stacks(t_all *all, int n)
{
	ft_bzero(&all->pred_cmds, sizeof(t_cmds));
	if (all->a.head == 0 || all->a.head->next == 0)
		return ;
	if (simple_rotate_algorithm(all, n))
		return ;
	else
		more_complex_algorithm(all, n);
}

int	simple_rotate_algorithm(t_all *all, int n)
{
	if (is_stack_sorted(&(all->a.head), n))
	{
		if (all->a.head->pos == 1)
			return (1);
		else
			rotate_until_sorted(all);
		return (1);
	}
	else
		return (0);
}

/*
** try to have the numbers in stack a in ascending order with the
** least number of moves.
** In case they are pushed to b they are placed in descending order
** Once a is in ascending order and b is in descending order
** all numbers are pushed from b to a.
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** Line-by-line comments:
** @4	sort a by swapping or pushing to b
** @5	merge a and b by pushing from b to a
*/

void	more_complex_algorithm(t_all *all, int n)
{
	t_all	temp;

	init_all(&temp, all, n);
	sort_a_b(all, n);
	merge_a_b(&all);
	if (!simple_rotate_algorithm(all, n))
		return ;
}

/* 		1 - In case there are numbers in b check if there's a good
 opportunity to push from b to a
 		2 - In case we find a number:
 			2.1 In case we can swap a number nearby we do it
 			2.2 In case there are no numbers nearby to swap push to B
 				(rotating b to push it in the right place)*/


/*
** we check the numbers before and after the current number
** looking for numbers that are not ascending order
** if they are not we either swap them if possible or 
** push them to b if not. once we have analyzed enough numbers 
** we execute the option that requires the least moves
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** Line-by-line comments:
** @3	check number after and iterate fwd 
** 		(e.g. 1 2 3 4 5 we will analyze 2 and prepare to analyze 3)
** @4	check number before and iterate bwd 
** 		(e.g. 1 2 3 4 5 we will analyze 5 and prepare to analyze 4)
*/


void	sort_a_b(t_all *all, int n)
{
	while (all->a.forw)
	{
		analyze_fwd(&all, n);
		analyze_bwd(&all, n);
		if (have_analyzed_enough(all))
		{
			execute_moves(&all->exec_cmds, &all->a, &all->b);
			init_stacks_iteration(&all->a, all->a.head);
			ft_bzero(&(all->a.ini_rot), sizeof(t_rot));
			ft_bzero(&all->pred_cmds, sizeof(t_cmds));
			ft_bzero(&all->exec_cmds, sizeof(t_cmds));
		}
		else if (all_number_checked(all))
			break ;
	}
}

void	merge_a_b(t_all **all)
{
	init_stacks_iteration(&(*all)->a, (*all)->a.head);
	ft_bzero(&((*all)->a.ini_rot), sizeof(t_rot));
	while ((*all)->b.head)
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		ft_bzero(&(*all)->b.ini_rot, sizeof(t_rot));
		place_in_a(*all);
		execute_merge_ab(&(*all)->pred_cmds, &(*all)->a, &(*all)->b);
	}
}
