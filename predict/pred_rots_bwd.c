/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_bwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:11:43 by gleal             #+#    #+#             */
/*   Updated: 2022/02/28 00:14:44 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_bwd;
	t_elem	*prev_bwd;

	check_bwd = pred->b.rev;
	prev_bwd = NULL;
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != (*target)->pos)
	{
		add_rrbs_find_next_bigger(all, pred, &check_bwd, &prev_bwd);
		if (check_bwd->pos == prev_bwd->pos)
			update_pred_b_head_bwd(pred, target, check_bwd);
		else
		{
			pred->b.rev = check_bwd;
			prev_bwd = check_bwd;
			rot_pred->rrb++;
		}
	}
	if (pred->b.forw->pos == (*target)->pos)
		(*target) = (*target)->prev;
}

void	add_rrbs_find_next_bigger(t_all *all, t_all *pred, t_elem **check_bwd, t_elem **prev_bwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while ((*check_bwd)->pos != pred->a.head->pos &&
		sent_stack->pos != pred->a.head->pos)
	{
		if ((is_bigger_than(sent_stack, pred->b.rev, pred->b.lims.min, pred->b.lims.max) || pred->b.rev->pos == sent_stack->pos)
			&& (*prev_bwd == NULL || is_bigger_than(*check_bwd, sent_stack, pred->b.lims.min, pred->b.lims.max)))
		{
			*check_bwd = sent_stack;
			*prev_bwd = *check_bwd;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

void	update_pred_b_head_bwd(t_all *pred, t_elem **target, t_elem	*check_bwd)
{

	if ((is_bigger_than((*target)->prev, pred->a.head, pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(pred->a.head, check_bwd, pred->b.lims.min, pred->b.lims.max))
		|| (is_bigger_than(check_bwd, pred->a.head, pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(pred->a.head, *target, pred->b.lims.min, pred->b.lims.max)))
			pred->b.forw = pred->a.head;
	else
		pred->b.forw = *target;
	if (is_bigger_than(check_bwd, *target,
			pred->b.lims.min, pred->b.lims.max))
	{
		pred->b.rev = *target;
		(*target) = (*target)->prev;
	}
	else
		pred->b.rev = pred->a.head;
}
