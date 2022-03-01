/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rrbs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:56:03 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 19:36:12 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

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
