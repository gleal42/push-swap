/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 23:28:06 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:26:20 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	pred_all_inirotsb(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	init_stacks_iteration(&pred->b, all->a.ramp.first_nbr);
	if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		return ;
	predict_all_ini_rbs(all, pred, rot_pred);
	predict_all_ini_rrbs(all, pred, rot_pred);
	calculate_initial_pushmoves(pred->b.near_rot.r,
		pred->b.near_rot.rrev, rot_pred);
}

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*temp;
	t_elem	*prev_temp;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	temp = sent_stack;
	prev_temp = temp;
	iterate_stack(&sent_stack, all->a.head);
	if (sent_stack->pos == pred->a.head->pos)
		return ;
	sent_stack = all->a.ramp.first_nbr;
	pred->b.forw = sent_stack;
	while (pred->b.forw->pos != pred->a.head->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_bigger_than(pred->b.rev, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
			&& (sent_stack->pos >= temp->pos))
			temp = sent_stack;
		if (sent_stack->pos == pred->a.head->pos)
		{
			if (temp->pos == prev_temp->pos)
				break ;
			else
			{
				prev_temp = temp;
				pred->b.forw = temp;
				rot_pred->rb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
	}
}

void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*temp;
	t_elem	*prev_temp;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	temp = sent_stack;
	prev_temp = temp;
	iterate_stack(&sent_stack, all->a.head);
	if (sent_stack->pos == pred->a.head->pos)
		return ;
	sent_stack = all->a.ramp.first_nbr;
	pred->b.rev = sent_stack;
	while (pred->b.rev->pos != pred->a.head->pos)
	{
		iterate_stack(&sent_stack, all->a.head);
		if (is_smaller_than(pred->b.rev, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
			&& (sent_stack->pos >= temp->pos))
			temp = sent_stack;
		if (sent_stack->pos == pred->a.head->pos)
		{
			if (temp->pos == prev_temp->pos)
				break ;
			else
			{
				prev_temp = temp;
				pred->b.rev = temp;
				rot_pred->rb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
	}
}
