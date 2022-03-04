/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_fwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:55:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 16:11:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	pred->b.fwd.cur = pred->b.forw;
	pred->b.fwd.next = NULL;
	while (pred->b.forw->pos != pred->a.head->pos
		&& pred->b.forw->pos != (*target)->pos)
	{
		add_rbs_find_next(all, pred, &pred->b.fwd.next);
		if (pred_enough_rots_fwd(pred, pred->b.fwd.cur,
				pred->b.fwd.next, *target))
			update_pred_b_fwd(pred, *target);
		else
		{
			rot_pred->rb++;
			pred->b.fwd.cur = pred->b.fwd.next;
			pred->b.fwd.next = NULL;
			pred->b.forw = pred->b.fwd.cur;
		}
	}
	if (pred->b.forw->pos == (*target)->pos)
	{
		rot_pred->rb++;
		iterate_stack(target, all->b.head);
	}
}

void	add_rbs_find_next(t_all *all, t_all *pred, t_elem **next_fwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if ((is_bigger_than(pred->b.forw, sent_stack,
					pred->b.lims.min, pred->b.lims.max))
			&& ((*next_fwd == NULL || is_bigger_than(sent_stack,
						*next_fwd, pred->b.lims.min, pred->b.lims.max))))
		{
			*next_fwd = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

int	pred_enough_rots_fwd(t_all *pred, t_elem *cur_fwd,
	t_elem *next_fwd, t_elem *target)
{
	if (!next_fwd)
		return (1);
	if (target && is_inbetween_bigger(cur_fwd, target, next_fwd, pred->b.lims))
		return (1);
	if (is_inbetween_bigger(cur_fwd, pred->a.head, next_fwd, pred->b.lims))
		return (1);
	return (0);
}

//update_pred_b_fwd(pred, pred->b.fwd.cur, pred->b.fwd.next, *target);

void	update_pred_b_fwd(t_all *pred, t_elem *target)
{
	if (!pred->b.fwd.next
		|| is_inbetween_bigger(pred->b.fwd.cur, target,
			pred->b.fwd.next, pred->b.lims))
	{
		if (is_inbetween_bigger(pred->b.fwd.cur, pred->a.head,
				target, pred->b.lims))
			pred->b.forw = pred->a.head;
		else
			pred->b.forw = target;
	}
	else
	{
		if (is_inbetween_bigger(pred->b.fwd.cur, pred->a.head,
				pred->b.fwd.next, pred->b.lims))
			pred->b.forw = pred->a.head;
		else
			pred->b.forw = target;
	}
}
