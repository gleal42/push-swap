/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 22:47:49 by gleal            ###   ########.fr       */
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
	all->a.ramp.init_cmds = all->pred_cmds;
	pred_ramp_rots(&pred, all, fst, &fst_ramp_val);
	pred_ramp_rots(&pred, all, all->a.ramp.first_nbr->prev, &scd_ramp_val);
	(&all->a.ramp.init_cmds)->total = count_moves(&all->a.ramp.init_cmds);
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
