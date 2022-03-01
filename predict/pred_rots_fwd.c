/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_fwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:55:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 20:23:22 by gleal            ###   ########.fr       */
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
		if (pred_enough_rots_fwd(pred, pred->b.fwd.cur, pred->b.fwd.next))
			update_pred_b_fwd(pred, pred->b.fwd.cur, pred->b.fwd.next, *target);
		else
		{
			pred->b.fwd.cur = pred->b.fwd.next;
			pred->b.fwd.next = NULL;
			pred->b.forw = pred->b.fwd.cur;
			rot_pred->rb++;
		}
	}
	if (pred->b.forw->pos == (*target)->pos)
		iterate_stack(target, all->b.head);
}

void	add_rbs_find_next(t_all *all, t_all *pred, t_elem **next_fwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if ((is_bigger_than(pred->b.forw, sent_stack,
					pred->b.lims.min, pred->b.lims.max))
			&& ((*next_fwd == NULL || is_smaller_than(sent_stack,
						*next_fwd, pred->b.lims.min, pred->b.lims.max))))
		{
			*next_fwd = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

int	pred_enough_rots_fwd(t_all *pred, t_elem *cur_fwd, t_elem *next_fwd)
{
	if (!next_fwd)
		return (1);
	else if (is_inbetween_bigger(cur_fwd, pred->a.head, next_fwd, pred->b.lims))
		return (1);
	return (0);
}

void	update_pred_b_fwd(t_all *pred, t_elem *cur_fwd,
		t_elem *next_fwd, t_elem *target)
{
	t_elem	*next;

	if (!next_fwd)
		next = target;
	else
		next = next_fwd;
	if (is_inbetween_bigger(cur_fwd, pred->a.head, next, pred->b.lims))
		pred->b.forw = pred->a.head;
	else
		pred->b.forw = target;
}
