/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:08:02 by gleal             #+#    #+#             */
/*   Updated: 2022/03/03 23:15:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	pred->b.fwd.cur = pred->b.forw;
	pred->b.fwd.next = NULL;
	while (pred->b.forw->pos != pred->a.head->pos)
	{
		add_rbs_find_next(all, pred, &pred->b.fwd.next);
		if (pred_enough_rots_fwd(pred, pred->b.fwd.cur, pred->b.fwd.next, NULL))
			pred->b.forw = pred->a.head;
		else
		{
			pred->b.fwd.cur = pred->b.fwd.next;
			pred->b.fwd.next = NULL;
			pred->b.forw = pred->b.fwd.cur;
			rot_pred->rb++;
		}
	}
}

void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	pred->b.bwd.cur = pred->b.rev;
	pred->b.bwd.prev = NULL;
	while (pred->b.rev->pos != pred->a.head->pos)
	{
		add_rrbs_find_prev(all, pred, &pred->b.bwd.prev);
		if (pred_enough_rots_bwd(pred, pred->b.bwd.prev, pred->b.bwd.cur))
			pred->b.rev = pred->a.head;
		else
		{
			pred->b.bwd.cur = pred->b.bwd.prev;
			pred->b.bwd.prev = NULL;
			pred->b.rev = pred->b.bwd.cur;
			rot_pred->rrb++;
		}
	}
}
