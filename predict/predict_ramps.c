/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/03/03 02:53:37 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

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
	all->a.ramp.init_cmds = all->pred_cmds;
	pred_ramp_rots(&pred, all, fst, &fst_ramp_val);
	pred_ramp_rots(&pred, all, all->a.ramp.first_nbr->prev, &scd_ramp_val);
	return (0);
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
	if (is_bigger_than(start_fstramp, head, lims->min, lims->max))
		return (1);
	else
		return (0);
}

void	pred_ramp_rots(t_all *pred, t_all *all,
		t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (valid(pred->a.head, ref, &pred->a.lims))
	{
		add_update_cmd(&all->a.ramp.init_cmds.pb, &all->a.ramp.init_cmds, 1);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		{
			place_in_b_rots(all->b.head, pred, pred->a.head,
				&all->a.ramp.init_cmds);
			if (all->a.ramp.init_cmds.rb || all->a.ramp.init_cmds.rr)
				pred->b.head = pred->b.forw;
			else if (all->a.ramp.init_cmds.rrb || all->a.ramp.init_cmds.rrr)
				pred->b.head = pred->b.rev;
			init_stacks_iteration(&pred->b, pred->b.head);
		}
		else
			pred_other_rots(pred, all, &all->a.ramp.init_cmds);
		if (all->a.ramp.best_cmds.total && all->a.ramp.init_cmds.total > all->a.ramp.best_cmds.total)
			return ;
		pred_lims_update(all->a.ramp.first_nbr, pred->b.head, all, pred);
		iterate_stack(&pred->a.head, all->a.head);
	}
}
