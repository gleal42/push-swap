/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_bwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:11:43 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 17:42:33 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

/*
** predicts all rrbs that can be added between the previously pushed number and
** either the number we will push now or the previous b (target)
** if we pushed 40 and the previous number in b is 35:
** if we will now push 37 then we will rotate to 37
** but if we will now push 32 then we will rotate to 35 so
** that we can rotate again in the next add_rrbs to 32
** @param:	- [t_all *] copy of all struct for this prediction
** 			- [t_all *] struct with all the variables
** 			- [t_elem **] previous non-predicted b
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
			update_pred_b_bwd(pred, *target);
		else
		{
			pred->b.bwd.cur = pred->b.bwd.prev;
			pred->b.bwd.prev = NULL;
			pred->b.rev = pred->b.bwd.cur;
			rot_pred->rrb++;
		}
	}
	if (pred->b.rev->pos == (*target)->pos)
	{
		(*target) = (*target)->prev;
		rot_pred->rrb++;
	}
}

int	pred_enough_rots_bwd(t_all *pred, t_elem *prev_bwd, t_elem *cur_bwd)
{
	if (!prev_bwd)
		return (1);
	if (is_inbetween_bigger(prev_bwd, pred->a.head, cur_bwd, pred->b.lims))
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
			&& (*prev_bwd == NULL || is_smaller_than(sent_stack, *prev_bwd,
					pred->b.lims.min, pred->b.lims.max)))
		{
			*prev_bwd = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

/*update_pred_b_bwd(pred, pred->b.bwd.prev,
	pred->b.bwd.cur, *target);*/

void	update_pred_b_bwd(t_all *pred, t_elem *target)
{
	if (!pred->b.bwd.prev
		|| is_inbetween_bigger(pred->b.bwd.prev, target,
			pred->b.bwd.cur, pred->b.lims))
	{
		if (is_inbetween_bigger(target, pred->a.head,
				pred->b.bwd.cur, pred->b.lims))
			pred->b.rev = pred->a.head;
		else
			pred->b.rev = target;
	}	
	else
	{
		if (is_inbetween_bigger(pred->b.bwd.prev, pred->a.head,
				pred->b.bwd.cur, pred->b.lims))
			pred->b.rev = pred->a.head;
		else
			pred->b.rev = target;
	}
}
