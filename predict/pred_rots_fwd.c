/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_fwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:55:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 17:42:59 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

/*
** predicts all rbs that can be added between the previously pushed number and
** either the number we will push now or the next b
** if we pushed 40 and the next number in b is 45:
** if we will now push 43 then we will rotate to 43
** but if we will now push 46 then we will rotate to 45 so
** that we can rotate again in the next add_rbs to 46
** @param:	- [t_all *] copy of all struct for this prediction
** 			- [t_all *] struct with all the variables
** 			- [t_elem **] next non-predicted b
** 			- [t_cmds *] current number rots prediction
** Line-by-line comments:
** @6	find next smaller number
** (smaller than current number but the next one so the 
** biggest of the smallest if that makes sense)
** so if we have pushed 2 3 4 if we are in 4 the next is 3 and not 2
** @7	we have reached either a target or the number we will push
** @8	we add a rb for previously pushed numbers and reset the analysis
**		for the next number
*/

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
