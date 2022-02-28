/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_fwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:27:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/27 19:08:31y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

//instead of bigger than target we must check better
//(maybe check if there are other bigger check_fwd)

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	pred->b.fwd.cur = pred->b.forw;
	pred->b.fwd.next = NULL;
	add_rbs_find_next(all, pred, &pred->b.fwd.next);
	if (pred_enough_rots_fwd(pred, pred->b.fwd.prev, pred->b.fwd.cur, pred->b.fwd.next, *target))
	{
		update_pred_b_fwd(pred, pred->b.fwd.prev, pred->b.fwd.cur, pred->b.fwd.next, *target); 
		if (pred->b.forw->pos == (*target)->pos)
			iterate_stack(target, all->b.head);
		return ;
	}
	else
	{
		pred->b.fwd.prev = pred->b.fwd.cur;
		pred->b.fwd.cur = pred->b.fwd.next;
		pred->b.forw = pred->b.fwd.cur;
		pred->b.fwd.next = NULL;
		rot_pred->rb++;
	}
	while (pred->b.forw->pos != pred->a.head->pos
		&& pred->b.forw->pos != (*target)->pos)
	{
		add_rbs_find_next(all, pred, &pred->b.fwd.next);
		if (pred_enough_rots_fwd(pred, pred->b.fwd.prev, pred->b.fwd.cur, pred->b.fwd.next, *target))
			update_pred_b_fwd(pred, pred->b.fwd.prev, pred->b.fwd.cur, pred->b.fwd.next, *target); 
		else
		{
			pred->b.fwd.prev = pred->b.fwd.cur;
			pred->b.fwd.cur = pred->b.fwd.next;
			pred->b.forw = pred->b.fwd.cur;
			pred->b.fwd.next = NULL;
			rot_pred->rb++;
		}
	}
	if (pred->b.forw->pos == (*target)->pos)
		iterate_stack(target, all->b.head);
}

// || (pred->b.forw->pos == sent_stack->pos)

void	add_rbs_find_next(t_all *all, t_all *pred, t_elem **next_fwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if ((is_bigger_than(pred->b.forw, sent_stack, pred->b.lims.min, pred->b.lims.max))
			&& ((*next_fwd == NULL || is_smaller_than(sent_stack, *next_fwd, pred->b.lims.min, pred->b.lims.max))))
		{
			*next_fwd = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

int	pred_enough_rots_fwd(t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target)
{
	if (!next_fwd)
		return (1);
	if (!prev_fwd)
	{
		if (is_inbetween_bigger(target->prev, pred->a.head, cur_fwd, pred->b.lims))
			return (1);
	}
	else if (is_inbetween_bigger(prev_fwd, pred->a.head, cur_fwd, pred->b.lims))
			return (1);
	return (0);
}

/*if (is_smaller_than(check_fwd, *target,
		pred->b.lims.min, pred->b.lims.max))*/

int	is_inbetween_bigger(t_elem *fst, t_elem *sec, t_elem *thrd, t_lims lims)
{
	if (is_bigger_than(fst, sec, lims.min, lims.max)
			&& is_bigger_than(sec, thrd, lims.min, lims.max))
		return (1);
	else
		return (0);
}

void	update_pred_b_fwd(t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target)
{
	t_elem	*prev;
	t_elem	*next;

	if (!prev_fwd)
		prev = target->prev;
	else
		prev = prev_fwd;
	if (!next_fwd)
		next = target;
	else
		next = next_fwd;
	if (is_inbetween_bigger(prev, pred->a.head, cur_fwd, pred->b.lims))
		pred->b.forw = pred->a.head;
	else
	{
		pred->b.fwd.prev = pred->b.forw;
		pred->b.forw = target;
	}
}