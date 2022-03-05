/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:45:17 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 18:44:45 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*
** Checks if numbers are already sorted. Sorts them in case they are not
** @param:	- [t_all *] struct with all the variables
** Line-by-line comments:
** @line-line	comment
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
** Combines 3 techniques to get the numbers in the right order:
** 		1 - In case there are numbers in b check if there's a good
** opportunity to push from b to a
** 		2 - In case we find a number:
** 			2.1 In case we can swap a number nearby we do it
** 			2.2 In case there are no numbers nearby to swap push to B
** 				(rotating b to push it in the right place)
** @param:	- [t_elem *] a
**			- [t_elem *] b
** Line-by-line comments:
** @line-line	comment
*/

void	more_complex_algorithm(t_all *all, int n)
{
	t_all	temp;

	init_all(&temp, all, n);
	sort_a_b(all);
	merge_a_b(&all);
	if (!simple_rotate_algorithm(all, n))
		return ;
}

void	sort_a_b(t_all *all)
{
	while (all->a.forw)
	{
		analyze_fwd(&all);
		analyze_bwd(&all);
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
