/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:59:20 by gleal             #+#    #+#             */
/*   Updated: 2022/02/09 16:24:01 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*
** Checks if numbers are already sorted. Sorts them in case they are not
** @param:	- [t_all *] struct with all the variables
** Line-by-line comments:
** @line-line	comment
*/

void	ft_sort_stacks(t_all *all, int max_len, int n)
{
	if (all->a == 0 || all->a->next == 0)
		return ;
	if (is_stack_sorted(&(all->a), n))
	{
		if (all->a->pos == 1)
			return ;
		else
			rotate_until_sorted(all, max_len);
	}
	else
		more_complex_algorithm(all, max_len, n);
}

void	rotate_until_sorted(t_all *all, int max_len)
{
	int		rotation_direction;

	rotation_direction = 0;
	all->forw_a = (all->a)->next;
	all->rev_a = (all->a)->prev;
	find_rotation_direction(all, &rotation_direction);
	while (all->a->pos != 1)
	{
		if (rotation_direction == RA)
			op_ra(&all->a, &all->b, max_len);
		else if (rotation_direction == RRA)
			op_rra(&all->a, &all->b, max_len);
	}
}

/*
** Combines 3 techniques to get the numbers in the right order:
** 		1 - In case there are numbers in b check if there's a good
** opportunity to push from b to a
** 		2 - In case we find a number:
** 			2.1 In case we can swap a number nearby we do it
** 			2.2 In case there are no numbers nearby to swap push to B
** 				(rotating b to push it in the right place)
** @param:	- [t_stack *] a
**			- [t_stack *] b
** Line-by-line comments:
** @line-line	comment
*/

/* don't forget that good in samne stack doesn't 
work well for 2 numbers in same stack
separate same stack from different stacks or add extra validation in if
*/

// else if (!temp.forw_a || temp.forw_a->pos == temp.rev_a->pos)

void	more_complex_algorithm(t_all *all, int max_a, int n)
{
	t_all	temp;

	init_lims(&temp, n);
	temp = *all;
	temp.forw_a = all->a;
	temp.rev_a = all->a;
	init_rots(&temp);
	init_cmd_list(&(all.cmds));
	while (temp.forw_a)
	{
		init_cmd_list(&(temp.cmds));
		if (is_next_nbr_bigger(temp.forw_a, (temp.forw_a)->next,
				temp.lims.min_a, temp.lims.max_a))
		{
			temp.ini_rot_a.ra++;
			temp.forw_a = temp.forw_a->next;
		}
		else
		{
			init_cmd_list(&(temp.cmds));
			if (is_good_for_swap(all->a, temp.forw_a, temp.lims.min_a,
					temp.lims.max_a))
			{
				temp.cmds.ra = temp.ini_rot_a.ra;
				swap_a(&temp, temp.forw_a, all->a);
				temp.ini_rot_a.ra++;
			}
			else
			{
				temp.ini_rot_a.ra++;
				temp.cmds.ra = temp.ini_rot_a.ra;
				merge_ramp_spot(all->a, all->b, &temp, temp.forw_a->next);
			}
			if (is_temp_better(temp.cmds, off.cmds))
				off.cmds = temp.cmds;
			temp.forw_a = temp.forw_a->next;
		}
		if (is_prev_nbr_smaller(temp.rev_a, temp.rev_a->prev,
				temp.lims.min_a, temp.lims.max_a))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;
		}
		else
		{
			init_cmd_list(&(temp.cmds));
			if (is_good_for_swap(all->a, temp.rev_a->prev,
					temp.lims.min_a, temp.lims.max_a))
			{
				temp.ini_rot_a.rra++;
				temp.cmds.rra = temp.ini_rot_a.rra;
				swap_a(&temp, temp.rev_a->prev, all->b);
			}
			else
			{
				temp.cmds.rra = temp.ini_rot_a.rra;
				merge_ramp_spot(all->a, all->b, &temp, temp.rev_a);
				temp.ini_rot_a.rra++;
			}
			if (is_temp_better(temp.cmds, off.cmds))
				off.cmds = temp.cmds;
			temp.rev_a = temp.rev_a->prev;
		}
		if (have_analyzed_enough(off.cmds, temp.ini_rot_a,
				temp.forw_a, temp.rev_a))
		{
			execute_moves(&off.cmds, &all->a, &all->b, &temp.lims, max_a);
			temp.forw_a = all->a;
			temp.rev_a = all->a;
			temp.ini_rot_a.ra = 0;
			temp.ini_rot_a.rra = 0;
			init_cmd_list(&(off.cmds));
		}
		else if (!temp.forw_a || temp.forw_a->pos == temp.rev_a->pos)
			break ;
	}
	temp.forw_a = all->a;
	temp.rev_a = all->a;
	temp.ini_rot_a.ra = 0;
	temp.ini_rot_a.rra = 0;
	while (all->b)
	{
		init_cmd_list(&(temp.cmds));
		min_push_b_to_a_moves(all->a, all->b, &temp);
		execute_merge_ab(&temp.cmds, &all->a, &all->b, &temp.lims, max_a);
	}
	if (is_stack_sorted(&all->a, n))
	{
		if ((all->a)->pos == 1)
			return ;
		else
			rotate_until_sorted(all, max_a);
	}
	else
		printf("WHOOPSIE\n");
}
