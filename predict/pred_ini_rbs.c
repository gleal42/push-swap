/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rbs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:08:02 by gleal             #+#    #+#             */
/*   Updated: 2022/02/27 18:09:29 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	pred->a.ramp.off_nbr = pred->b.forw;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	while (pred->b.forw->pos != pred->a.head->pos)
	{
		ini_rbs_find_next_lower(all, pred);
		if (pred->a.ramp.off_nbr->pos == pred->a.ramp.prev_nbr->pos)
			pred->b.forw = pred->a.head;
		else
			ini_update_pred_rbs_elem(pred, &rot_pred->rb);
	}
}

void	ini_rbs_find_next_lower(t_all *all, t_all *pred)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (pred->a.ramp.off_nbr->pos != pred->a.head->pos
			&& sent_stack->pos != pred->a.head->pos)
	{
		if (is_bigger_than(pred->b.forw, sent_stack,
				pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(sent_stack, pred->a.ramp.off_nbr,
				pred->b.lims.min, pred->b.lims.max))
		{
			pred->a.ramp.off_nbr = sent_stack;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

void	ini_update_pred_rbs_elem(t_all *pred, int *rot_pred)
{
	pred->b.forw = pred->a.ramp.off_nbr;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	(*rot_pred)++;
}
