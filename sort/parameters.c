/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:52:01 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 13:41:29y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

int	is_cmd_table_clean(t_cmds cmds)
{
	if (cmds.sa <= 0
		&& cmds.sb <= 0
		&& cmds.ss <= 0
		&& cmds.ra <= 0
		&& cmds.rb <= 0
		&& cmds.rr <= 0
		&& cmds.pa <= 0
		&& cmds.pb <= 0
		&& cmds.rra <= 0
		&& cmds.rrr <= 0
		&& cmds.rrb <= 0)
		return (1);
	else
		return (0);
}

/*  
* See which is best metric for every size of ramp
*/
/* temp_rotates_per_push = (temp_cmd.rb + temp_cmd.rrb)/temp_cmd.pb;
off_ratio = (off_cmd.rb + off_cmd.rrb)/off_cmd.pb;
if (temp_ratio < off_ratio)
if (temp_cmd.total < off_cmd.total && temp_rotates_per_push
< off_rotates_per_push) */

int	is_better_ramp(t_cmds temp_cmd, t_cmds off_cmd)
{
	float	temp_rotates_per_push;
	float	off_rotates_per_push;

	if (!off_cmd.total)
		return (1);
	temp_rotates_per_push = temp_cmd.total / temp_cmd.pb;
	off_rotates_per_push = off_cmd.total / off_cmd.pb;
	if (temp_cmd.total < off_cmd.total)
		return (1);
	else
		return (0);
}

int	continue_ramp_analysis(t_stack *a, t_stack	*first_nbr, t_all *temp)
{
	(void)a;
	if (is_prev_nbr_smaller(first_nbr, first_nbr->prev,
			temp->lims.min_a, temp->lims.max_a))
		return (1);
	else
		return (0);
}

int	have_analyzed_enough(t_cmds off, t_rot_a ini_rot_a,
		t_stack *forw_a, t_stack *rev_a)
{
	if (off.total)
	{
		if (off.total < ini_rot_a.ra)
			return (1);
		if (off.total < ini_rot_a.rra)
			return (1);
		if (!forw_a)
			return (1);
		if (forw_a->pos == rev_a->pos)
			return (1);
	}
	return (0);
}

int	is_temp_better(t_cmds temp, t_cmds off)
{	
	if (!(off.total))
		return (1);
	if (temp.type == SWAP_BWD || temp.type == SWAP_FWD)
	{
		if (off.type == PUSH_B_BWD || off.type == PUSH_B_FWD)
		{
			if (temp.total < off.total + 2)
				return (1);
			else
				return (0);
		}
		else
		{
			if (temp.total < off.total)
				return (1);
			else
				return (0);
		}
	}
	if (temp.total < off.total)
		return (1);
	else
		return (0);
}

int	is_good_for_swap(t_stack *first, t_stack *to_be_swaped,
		int min_stack, int max_stack)
{
	if (!first)
		return (0);
	if (!first->next)
		return (0);
	if (!first->next->next)
		return (0);
	if (!to_be_swaped->next)
	{
		if (is_next_nbr_bigger(to_be_swaped, first->next,
				min_stack, max_stack)
			&& is_prev_nbr_smaller(first, to_be_swaped->prev,
					min_stack, max_stack))
			return (1);
	}
	else
	{
		if (!to_be_swaped->next->next)
		{
			if (is_next_nbr_bigger(to_be_swaped, first,
					min_stack, max_stack)
				&& is_prev_nbr_smaller(to_be_swaped->next,
						to_be_swaped->prev, min_stack, max_stack))
				return (1);
		}
		else
		{
			if (is_next_nbr_bigger(to_be_swaped, to_be_swaped->next->next,
					min_stack, max_stack)
				&& is_prev_nbr_smaller(to_be_swaped->next,
						to_be_swaped->prev, min_stack, max_stack))
				return (1);
		}
	}
	return (0);
}

int	is_next_nbr_bigger(t_stack *cur, t_stack *next_one,
		int min_stack, int max_stack)
{
	if (!next_one)
		return (1);
	if (cur->pos <= min_stack && next_one->pos >= max_stack)
		return (0);
	if (next_one->pos > cur->pos)
		return (1);
	if (cur->pos >= max_stack && next_one->pos <= min_stack)
		return (1);
	return (0);
}

int	is_prev_nbr_smaller(t_stack *cur, t_stack *prev_one,
		int min_stack, int max_stack)
{
	if (!prev_one)
		return (1);
	if (cur->pos >= max_stack && prev_one->pos <= min_stack)
		return (0);
	if (prev_one->pos < cur->pos)
		return (1);
	if (cur->pos <= min_stack && prev_one->pos >= max_stack)
		return (1);
	return (0);
}

int	is_stack_sorted(t_stack **a, int n)
{
	t_stack	*temp;

	temp = *a;
	while (temp->next)
	{
		if(!is_next_nbr_bigger(temp, temp->next, 1, n))
			return (0);
		temp = temp->next;
	}
	if (!is_next_nbr_bigger(temp, *a, 1, n))
		return (0);
	else
		return (1);
}
