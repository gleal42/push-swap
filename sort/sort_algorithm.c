/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:43:16 by gleal             #+#    #+#             */
/*   Updated: 2021/07/15 22:14:26by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort.h"

void	rotate_until_sorted(t_stack **a, t_stack **b, int max_len)
{
	int rotation_direction;

	t_stack *norm;
	t_stack *rev;
	rotation_direction = 0;

	norm = (*a)->next;
	rev = (*a)->prev;
	while (!rotation_direction && norm)
	{
		if (norm->pos == 1)
			rotation_direction = RA;
		else if (rev->pos == 1)
			rotation_direction = RRA;
		if (norm->pos == rev->pos)
			break ;
		norm = norm->next;
		if (norm->pos == rev->pos)
			break ;
		rev = rev->prev;	
	}
	if (!rotation_direction)
		return ;
	while ((*a)->pos != 1)
	{
		if (rotation_direction == RA)
			op_ra(a, b, max_len);
		else if (rotation_direction == RRA)
			op_rra(a, b, max_len);
	}
}

void	ft_sort_stacks(t_stack **a, t_stack **b, int max_len, int n)
{
	if (*a == 0 || (*a)->next == 0)
		return ;
	if (is_stack_sorted(a, n))
	{
		if ((*a)->pos == 1)
			return ;
		else
			rotate_until_sorted(a, b, max_len);
	}
	else 
		more_complex_algorithm(a, b, max_len, n);
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

/* don't forget that good in samne stack doesn't work well for 2 numbers in same stack
	separate same stack from different stacks or add extra validation in if*/

// else if (!temp.forw_a || temp.forw_a->pos == temp.rev_a->pos)

void	more_complex_algorithm(t_stack **a, t_stack **b, int max_a, int n)
{
	t_all off;
	t_all temp;

	int	last;

	last = 0;
	temp.lims.min_a = 1;
	temp.lims.max_a = n;
	temp.lims.min_b = 0;
	temp.lims.max_b = 0;
	temp.forw_a = *a;
	temp.rev_a = *a;
	temp.ini_rot_a.ra = 0;
	temp.ini_rot_a.rra = 0;
	init_cmd_list(&(off.cmds));
	while (temp.forw_a)
	{
		init_cmd_list(&(temp.cmds));
		if (is_next_nbr_bigger(temp.forw_a, (temp.forw_a)->next, temp.lims.min_a, temp.lims.max_a))
		{
			temp.ini_rot_a.ra++;
			temp.forw_a = temp.forw_a->next;
		}
		else
		{
			init_cmd_list(&(temp.cmds));
			if (is_good_for_swap(*a, temp.forw_a, temp.lims.min_a, temp.lims.max_a))
			{
				temp.cmds.ra = temp.ini_rot_a.ra;
				swap_a(&temp, temp.forw_a, *b);
				temp.ini_rot_a.ra++;
			}
			else
			{
				temp.ini_rot_a.ra++;
				temp.cmds.ra = temp.ini_rot_a.ra;
				merge_ramp_spot(*a, *b, &temp, temp.forw_a->next);
			}
			if (is_temp_better(temp.cmds, off.cmds))
				off.cmds = temp.cmds;
			temp.forw_a = temp.forw_a->next;
		}
		if (is_prev_nbr_smaller(temp.rev_a, temp.rev_a->prev, temp.lims.min_a, temp.lims.max_a))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;	
		}
		else
		{
			init_cmd_list(&(temp.cmds));
			if (is_good_for_swap(*a, temp.rev_a->prev, temp.lims.min_a, temp.lims.max_a))
			{
				temp.ini_rot_a.rra++;
				temp.cmds.rra = temp.ini_rot_a.rra;
				swap_a(&temp, temp.rev_a->prev, *b);
			}
			else
			{
				temp.cmds.rra = temp.ini_rot_a.rra;
				merge_ramp_spot(*a, *b, &temp, temp.rev_a);
				temp.ini_rot_a.rra++;
			}
			if (is_temp_better(temp.cmds, off.cmds))
				off.cmds = temp.cmds;
			temp.rev_a = temp.rev_a->prev;	
		}
 		if (have_analyzed_enough(off.cmds, temp.ini_rot_a, temp.forw_a, temp.rev_a))
		{
			execute_moves(&off.cmds, a, b, &temp.lims, max_a);
			temp.forw_a = *a;
			temp.rev_a = *a;
			temp.ini_rot_a.ra = 0;
			temp.ini_rot_a.rra = 0;
			init_cmd_list(&(off.cmds));
		} 
		else if (!temp.forw_a || temp.forw_a->pos == temp.rev_a->pos)
			break ;
	}
	temp.forw_a = *a;
	temp.rev_a = *a;
	temp.ini_rot_a.ra = 0;
	temp.ini_rot_a.rra = 0;
	while (*b)
	{
		init_cmd_list(&(temp.cmds));
		min_push_b_to_a_moves(*a, *b, &temp);
		execute_merge_ab(&temp.cmds, a, b, &temp.lims, max_a);
	}
	if (is_stack_sorted(a, n))
	{
		if ((*a)->pos == 1)
			return ;
		else
			rotate_until_sorted(a, b, max_a);
	}
	else
		printf("WHOOPSIE\n");
}