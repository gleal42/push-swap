/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 19:06:23 by gleal            ###   ########.fr       */
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
	pred_ramp_rots(&pred, all, fst, &fst_ramp_val);
	pred_ramp_rots(&pred, all, all->a.ramp.first_nbr->prev, &scd_ramp_val);
	(&all->a.ramp.init_cmds)->total = count_moves(&all->a.ramp.init_cmds);
	return (0);
}

void	pred_ramp_rots(t_all *pred, t_all *all, t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (valid(pred->a.head, ref, &pred->a.lims))
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(all->a.ramp.first_nbr, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
			place_in_b(all->b.head, pred, pred->a.head, &all->a.ramp.init_cmds);
		else
		{
			pred_other_rots(&all->a.ramp.init_cmds, all->a.head, all->b.head,
				all->a.ramp.first_nbr, pred->a.head,
				&pred->b.head, all, &pred->b.lims);
		}
		update_cur_b(&all->a.ramp.init_cmds, &pred->b.head, pred->b.forw, pred->b.rev);
		iterate_stack(&pred->a.head, all->a.head);
	}
}

int	fst_ramp_val(t_elem *head, t_elem *start_secramp, t_lims *lims)
{
	(void)lims;
	if (head->pos != start_secramp->pos)
		return (1);
	else
		return (0);
}

int	scd_ramp_val(t_elem *head, t_elem *start_fstramp, t_lims *lims)
{
	if (!is_next_nbr_bigger(start_fstramp, head,
			lims->min, lims->max))
			return (1);
	else
		return (0);
}

/* void	pred_fst_ramp_rots(t_all *pred, t_all *all, t_elem *fst, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (pred->a.head->pos != fst->pos)
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(fst, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
			place_in_b(all->b.head, pred, pred->a.head, &all->a.ramp.init_cmds);
		else
		{
			pred_other_rots(&all->a.ramp.init_cmds, all->a.head, all->b.head,
				all->a.ramp.first_nbr, pred->a.head,
				&pred->b.head, all, &pred->b.lims);
		}
		update_cur_b(&all->a.ramp.init_cmds, pred->b.head, pred->b.forw, pred->b.rev);
		iterate_stack(&pred->a.head, all->a.head);
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
 */