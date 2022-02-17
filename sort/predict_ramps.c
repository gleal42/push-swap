/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 00:33:19 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* 
considerar fazer apenas predict_rotationsb caso tenha mais que 100 algarismos
(porque com 100 está melhor sem isso acho eu)
first prediction pode ser com aquele predictmoves 
*/

/* 2nd while line 20 maybe cur_a->next is not
the best here (for the cases where there is no next) */

int	pred_ramp_moves(t_all *all, t_elem *fst)
{
	t_all	pred;

	pred = *all;
	pred.a.head = all->a.ramp.first_nbr;
	pred.b.head = all->b.head;
	pred_fst_ramp_rots(&pred, all, fst);
	pred_scd_ramp_rots(&pred, all, fst);
	(&all->a.ramp.init_cmds)->total = count_moves(&all->a.ramp.init_cmds);
	return (0);
}

void	pred_fst_ramp_rots(t_all *pred, t_all *all, t_elem *fst)
{
	while (pred->a.head->pos != fst->pos)
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(fst, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
			pred_ini_rots(&all->a.ramp.init_cmds,
				all->b.head, pred->a.head, &pred->b.head, pred);
		else
			pred_other_rots(&all->a.ramp.init_cmds, all->a.head, all->b.head,
				all->a.ramp.first_nbr, pred->a.head,
				&pred->b.head, all, &pred->b.lims);
		if (!pred->a.head->next)
			pred->a.head = all->a.head;
		else
			pred->a.head = pred->a.head->next;
	}
}

void	pred_scd_ramp_rots(t_all *pred, t_all *all, t_elem *fst)
{
	while (!is_next_nbr_bigger(all->a.ramp.first_nbr->prev, pred->a.head,
			pred->a.lims.min, pred->a.lims.max))
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(fst, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
			pred_ini_rots(&all->a.ramp.init_cmds,
				all->b.head, pred->a.head, &pred->b.head, all);
		else
			pred_other_rots(&all->a.ramp.init_cmds, all->a.head, all->b.head,
				all->a.ramp.first_nbr, pred->a.head,
				&pred->b.head, all, &pred->b.lims);
		if (!pred->a.head->next)
			pred->a.head = all->a.head;
		else
			pred->a.head = pred->a.head->next;
	}
}
