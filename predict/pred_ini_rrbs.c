/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rrbs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:56:03 by gleal             #+#    #+#             */
/*   Updated: 2022/02/27 18:17:47 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"


/*	pred->a.ramp.sent = all->a.ramp.first_nbr;
	pred->a.ramp.off_nbr = pred->a.ramp.sent;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	iterate_stack(&pred->a.ramp.sent, all->a.head);
	if (pred->a.ramp.sent->pos == pred->a.head->pos)
		return ;
	pred->a.ramp.sent = all->a.ramp.first_nbr;
	pred->b.rev = pred->a.ramp.sent;
	while (pred->b.rev->pos != pred->a.head->pos)
	{
		iterate_stack(&pred->a.ramp.sent, all->a.head);
		predict_next_ini_rrb_nbr(pred);
		if (update_pred_rrbs_reset(all, pred, &rot_pred->rrb))
			break ;
	}*/

/*	
	pred->a.ramp.off_nbr = pred->b.forw;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	while (pred->b.forw->pos != pred->a.head->pos)
	{
		ini_rbs_find_next_lower(all, pred);
		if (pred->a.ramp.off_nbr->pos == pred->a.ramp.prev_nbr->pos)
			pred->b.forw = pred->a.head;
		else
			ini_update_pred_rbs_elem(pred, &rot_pred->rb);
	}*/

void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	pred->a.ramp.off_nbr = pred->b.rev;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	while (pred->b.rev->pos != pred->a.head->pos)
	{
		ini_rrbs_find_next_bigger(all, pred);
		if (pred->a.ramp.off_nbr->pos == pred->a.ramp.prev_nbr->pos)
			pred->b.rev = pred->a.head;
		else
			ini_update_pred_rrbs_elem(pred, &rot_pred->rb);
	}
}

void	ini_rrbs_find_next_bigger(t_all *all, t_all *pred)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (pred->a.ramp.off_nbr->pos != pred->a.head->pos
			&& sent_stack->pos != pred->a.head->pos)
	{
		if (is_smaller_than(pred->b.rev, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
			&& is_smaller_than(sent_stack, pred->a.ramp.off_nbr,
				pred->b.lims.min, pred->b.lims.max))
		{
			pred->a.ramp.off_nbr = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

void	ini_update_pred_rrbs_elem(t_all *pred, int *rot_pred)
{
	pred->b.forw = pred->a.ramp.off_nbr;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	(*rot_pred)++;
}
