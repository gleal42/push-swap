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

/* We need:
* To have something to update the
* current b (because when we rotate the head changes)
* To keep track of the numbers we have
* already pushed (in case we need to go backwards)
*/

int	pred_other_rots(t_all *pred, t_all *all, t_lims *lims_b, t_cmds *temp_cmd)
{
	t_cmds	rot_pred;

	pred->b.near_rot.r = 0;
	pred->b.near_rot.rrev = 0;
	ft_bzero(&rot_pred, sizeof(t_cmds));
	pred_min_rots(all, pred, &rot_pred);
	if (is_good_to_place_wo_rot_b(all->b.head, pred->a.head, all->b.lims))
	{
		calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
		return (0);
	}
	init_stacks_iteration(&pred->b, pred->b.head);
	while (!pred->b.near_rot.r || !pred->b.near_rot.rrev)
	{
		iterate_fwd_rev_noend(&pred->b, all->b.head);
		add_rbs(all, pred, &rot_pred);
		add_rrbs(all, pred, &rot_pred);
		check_if_found_rot(pred->a.head, &all->b, &pred->b.near_rot, all->b.lims);
	}
	calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
	if (rot_pred.rb)
		pred->b.head = pred->b.forw;
	else if (rot_pred.rrb)
		pred->b.head = pred->b.rev;
	update_cur_b(&rot_pred, &pred->b.head, all->b.forw, all->b.rev);
	temp_cmd->rb += rot_pred.rb;
	temp_cmd->rrb += rot_pred.rrb;
	return (0);
}


void	pred_min_rots(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*sent_stack;
	t_elem	*check_fwd;
	t_elem	*check_bwd;

	init_stacks_iteration(pred->b, all->a.ramp.first_nbr);
	if (pred->a.head->pos == all->a.ramp.first_nbr)
		return ;
	sent_stack = all->a.ramp.first_nbr;
	while (pred->b.forw != pred->a.head->pos 
			&& pred->b.rev != pred->a.head->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_smaller_than(pred->b.forw, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos < check->pos)
			check_fwd = sent_stack;
		if (is_bigger_than(pred->b.rev, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check->pos)
			check_bwd = sent_stack;
		if(sent_stack == pred->a.head->pos)
		{
			pred->b.forw = check_fwd;
			pred->b.rev = check_bwd;
			rot_pred->rb++;
			rot_pred->rrb++;
			sent_stack = all->a.ramp.first_nbr;
		}
		if (pred->b.forw == pred->a.head->pos)
			rot_pred->rrb = 0;
		else if (pred->b.rev == pred->a.head->pos)
			rot_pred->rb = 0;
	}
}

/*
* Consider the numbers that were already pushed in case the next number
* Check if it is considering the right numbers
*/

void	add_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*sent_stack;
	t_elem	*check_fwd;
	t_elem	*min;

	if (pred->a.head->pos == all->a.ramp.first_nbr)
		return ;
	sent_stack = all->a.ramp.first_nbr;
	while (min->pos != pred->a.forw->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_bigger_than(sent_stack, 
				pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check->pos)
			check_fwd = sent_stack;
		if(sent_stack == pred->a.head->pos)
		{
			rot_pred->rb++;
			sent_stack = all->a.ramp.first_nbr;
		}
		if (pred->b.forw == pred->a.head->pos)
			rot_pred->rrb = 0;
		else if (pred->b.rev == pred->a.head->pos)
			rot_pred->rb = 0;
	}
}

/* este foi copiado de cima, ver se faz sentido
ou que modificações é preciso fazer.
utilizar os prev era top
 */

void	add_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*sent_stack;
	t_elem	*next;

	next = pred->b.rev;
	iterate_stack(&next, all->b.head);
	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if (is_bigger_than(pred->b.rev, sent_stack,
			pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(sent_stack, next,
				pred->b.lims.min, pred->b.lims.max))
			rot_pred->rrb++;
		iterate_stack(&sent_stack, all->a.head);
	}
}