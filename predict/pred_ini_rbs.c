/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rbs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:08:02 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 19:30:36 by gleal            ###   ########.fr       */
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
		if (pred_enough_rots_fwd(pred, pred->b.fwd.cur, pred->b.fwd.next))
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
