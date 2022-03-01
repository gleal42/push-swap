/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_bwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:11:43 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 20:37:33 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	pred->b.bwd.cur = pred->b.rev;
	pred->b.bwd.prev = NULL;
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != (*target)->pos)
	{
		add_rrbs_find_prev(all, pred, &pred->b.bwd.prev);
		if (pred_enough_rots_bwd(pred, pred->b.bwd.prev,
				pred->b.bwd.cur))
			update_pred_b_bwd(pred, pred->b.bwd.prev,
				pred->b.bwd.cur, *target);
		else
		{
			pred->b.bwd.cur = pred->b.bwd.prev;
			pred->b.bwd.prev = NULL;
			pred->b.rev = pred->b.bwd.cur;
			rot_pred->rrb++;
		}
	}
	if (pred->b.rev->pos == (*target)->pos)
		(*target) = (*target)->prev;
}

int	pred_enough_rots_bwd(t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd)
{
	if (!prev_fwd)
		return (1);
	if (is_inbetween_bigger(prev_fwd, pred->a.head, cur_fwd, pred->b.lims))
		return (1);
	return (0);
}

void	add_rrbs_find_prev(t_all *all, t_all *pred, t_elem **prev_bwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if (is_bigger_than(sent_stack, pred->b.rev,
				pred->b.lims.min, pred->b.lims.max)
			&& (*prev_bwd == NULL || is_bigger_than(*prev_bwd,
					sent_stack, pred->b.lims.min, pred->b.lims.max)))
		{
			*prev_bwd = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

void	update_pred_b_bwd(t_all *pred, t_elem *prev_bwd,
		t_elem *cur_bwd, t_elem *target)
{
	t_elem	*prev;

	if (!prev_bwd)
		prev = target;
	else
		prev = prev_bwd;
	if (is_inbetween_bigger(prev, pred->a.head, cur_bwd, pred->b.lims))
		pred->b.rev = pred->a.head;
	else
		pred->b.rev = target;
}
