/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_bwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:11:43 by gleal             #+#    #+#             */
/*   Updated: 2022/02/28 18:00:45 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

/*
	pred->b.fwd.prev = pred->b.fwd.cur;
	pred->b.fwd.cur = pred->b.fwd.next;
	pred->b.forw = pred->b.fwd.cur;
	pred->b.fwd.next = NULL;
	rot_pred->rb++;
*/

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	pred->b.bwd.cur = pred->b.rev;
	pred->b.bwd.prev = NULL;
	add_rrbs_find_prev(all, pred, &pred->b.bwd.prev);
	if (pred_enough_rots_bwd(all, pred, pred->b.bwd.prev, pred->b.bwd.cur, pred->b.bwd.next, *target))
	{
		update_pred_b_bwd(all, pred, pred->b.bwd.prev, pred->b.bwd.cur, pred->b.bwd.next, *target);
		if (pred->b.rev->pos == (*target)->pos)
			(*target) = (*target)->prev;
		return ;
	}
	else
	{
		pred->b.bwd.next = pred->b.bwd.cur;
		pred->b.bwd.cur = pred->b.bwd.prev;
		pred->b.rev = pred->b.bwd.cur;
		pred->b.bwd.prev = NULL;
		rot_pred->rrb++;
	}
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != (*target)->pos)
	{
		add_rrbs_find_prev(all, pred, &pred->b.bwd.prev);
		if (pred_enough_rots_bwd(all, pred, pred->b.bwd.prev, pred->b.bwd.cur, pred->b.bwd.next, *target))
		{
			update_pred_b_bwd(all, pred, pred->b.bwd.prev, pred->b.bwd.cur, pred->b.bwd.next, *target);
			return ;
		}
		else
		{
			pred->b.bwd.next = pred->b.bwd.cur;
			pred->b.bwd.cur = pred->b.bwd.prev;
			pred->b.rev = pred->b.bwd.cur;
			pred->b.bwd.prev = pred->b.bwd.cur;
			rot_pred->rrb++;
		}
	}
	if (pred->b.rev->pos == (*target)->pos)
		(*target) = (*target)->prev;
}

int	pred_enough_rots_bwd(t_all *all, t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target)
{
	t_elem *temp_target;

	temp_target = target;
	iterate_stack(&temp_target, all->b.head);
	if (!prev_fwd)
		return (1);
	if (!next_fwd)
	{
		if (is_inbetween_bigger(cur_fwd, pred->a.head, temp_target, pred->b.lims))
			return (1);
	}
	else if (is_inbetween_bigger(prev_fwd, pred->a.head, cur_fwd, pred->b.lims))
			return (1);
	return (0);
}

void	add_rrbs_find_prev(t_all *all, t_all *pred, t_elem **prev_bwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if (is_bigger_than(sent_stack, pred->b.rev, pred->b.lims.min, pred->b.lims.max)
			&& (*prev_bwd == NULL || is_bigger_than(*prev_bwd, sent_stack, pred->b.lims.min, pred->b.lims.max)))
		{
			*prev_bwd = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

void	update_pred_b_bwd(t_all *all, t_all *pred, t_elem *prev_bwd, t_elem *cur_bwd, t_elem *next_bwd, t_elem *target)
{
	t_elem	*prev;
	t_elem	*next;
	t_elem *temp_target;

	temp_target = target;
	iterate_stack(&temp_target, all->b.head);
	if (!prev_bwd)
		prev = target;
	else
		prev = prev_bwd;
	if (!next_bwd)
		next = temp_target;
	else
		next = next_bwd;
	if (is_inbetween_bigger(prev, pred->a.head, cur_bwd, pred->b.lims))
		pred->b.rev = pred->a.head;
	else
	{
		pred->b.bwd.next = pred->b.rev;
		pred->b.rev = target;
	}
}
