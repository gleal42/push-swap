/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:22:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/18 18:45:08by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	pred_ramp_rots(t_all *pred, t_all *all, t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (valid(pred->a.head, ref, &pred->a.lims))
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(all->a.ramp.first_nbr, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		{
			place_in_b(all->b.head, pred, pred->a.head, &all->a.ramp.init_cmds);
			if (all->a.ramp.init_cmds.rb || all->a.ramp.init_cmds.rr)
				pred->b.head = pred->b.forw;
			else if (all->a.ramp.init_cmds.rrb || all->a.ramp.init_cmds.rrr)
				pred->b.head = pred->b.rev;
		}
		else
			pred_other_rots(pred, all, &all->a.ramp.init_cmds);	
		iterate_stack(&pred->a.head, all->a.head);
	}
}

/* We need:
* To have something to update the
* current b (because when we rotate the head changes)
* To keep track of the numbers we have
* already pushed (in case we need to go backwards)
*/

int	pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd)
{
	t_cmds	rot_pred;

	pred->b.near_rot.r = 0;
	pred->b.near_rot.rrev = 0;
	ft_bzero(&rot_pred, sizeof(t_cmds));
	if (!all->b.head || !all->b.head->next)
	{
		pred_all_inirotsb(all, pred, &rot_pred);
		calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
		temp_cmd->rb += rot_pred.rb;
		temp_cmd->rrb += rot_pred.rrb;
		return (0);
	}
	init_stacks_iteration(&pred->b, pred->b.head);
	pred_start_rotsb(all, pred, &rot_pred);
	while (!pred->b.near_rot.r || !pred->b.near_rot.rrev)
	{
		iterate_fwd_rev_noend(&pred->b, all->b.head);
		add_rbs(all, pred, &rot_pred);
		add_rrbs(all, pred, &rot_pred);
		check_if_found_rot(pred->a.head, &all->b, &pred->b.near_rot, pred->b.lims);
	}
	calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
	iterate_stack(&pred->a.head, all->a.head);
	if (rot_pred.rb)
		pred->b.head = pred->b.forw;
	else if (rot_pred.rrb)
		pred->b.head = pred->b.rev;
	temp_cmd->rb += rot_pred.rb;
	temp_cmd->rrb += rot_pred.rrb;
	return (0);
}

void	pred_start_rotsb(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*check_fwd;
	t_elem	*check_bwd;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (pred->b.forw->pos != pred->b.head->pos
		|| pred->b.rev->pos != pred->b.head->prev->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_bigger_than(pred->b.rev, sent_stack,
			pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check_fwd->pos)
			check_fwd = sent_stack;
		if (is_smaller_than(pred->b.forw, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos < check_bwd->pos)
			check_bwd = sent_stack;
		if(sent_stack->pos == pred->a.head->pos)
		{
			if (is_bigger_than(sent_stack, pred->b.head,
			pred->b.lims.min, pred->b.lims.max))
			{
				pred->b.forw = check_fwd;
				rot_pred->rb++;
			}
			if (is_smaller_than(sent_stack, pred->b.head->prev,
				pred->b.lims.min, pred->b.lims.max))
			{
				pred->b.rev = check_bwd;
				rot_pred->rrb++;
			}
			sent_stack = all->a.ramp.first_nbr;
		}
	}
}

/*
* Consider the numbers that were already pushed in case the next number
* Check if it is considering the right numbers
*/

void	add_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*check_fwd;
	t_elem	*min;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	min = sent_stack;
	while (min->pos != pred->b.forw->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_bigger_than(pred->b.rev, sent_stack,
			pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check_fwd->pos)
			check_fwd = sent_stack;
		if(sent_stack->pos == pred->a.head->pos)
		{
			if (is_bigger_than(sent_stack, pred->b.forw,
			pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(pred->b.forw->prev, sent_stack, 
			pred->b.lims.min, pred->b.lims.max))
			{
				pred->b.forw = check_fwd;
				rot_pred->rb++;
			}
			else
				min = pred->b.forw;
			sent_stack = all->a.ramp.first_nbr;
		}
	}
}

/* este foi copiado de cima, ver se faz sentido
ou que modificações é preciso fazer.
utilizar os prev era top
 */

void	add_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*check_bwd;
	t_elem	*max;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	max = sent_stack;
	while (max->pos != pred->b.rev->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_bigger_than(pred->b.rev, sent_stack,
			pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check_bwd->pos)
			check_bwd = sent_stack;
		if(sent_stack->pos == pred->a.head->pos)
		{
			if (is_bigger_than(sent_stack, pred->b.forw,
			pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(pred->b.forw->prev, sent_stack, 
			pred->b.lims.min, pred->b.lims.max))
			{
				pred->b.forw = check_bwd;
				rot_pred->rb++;
			}
			else
				max = pred->b.forw;
			sent_stack = all->a.ramp.first_nbr;
		}
	}
}