/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rots2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:56:03 by gleal             #+#    #+#             */
/*   Updated: 2022/02/25 18:58:36 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	pred->a.ramp.sent = all->a.ramp.first_nbr;
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
	}
}

void	predict_next_ini_rrb_nbr(t_all *pred)
{
	if (is_smaller_than(pred->b.rev, pred->a.ramp.sent,
			pred->b.lims.min, pred->b.lims.max)
		&& (pred->a.ramp.sent->pos >= pred->a.ramp.off_nbr->pos))
		pred->a.ramp.off_nbr = pred->a.ramp.sent;
}

int	update_pred_rrbs_reset(t_all *all, t_all *pred, int *rot_pred)
{
	if (pred->a.ramp.sent->pos == pred->a.head->pos)
	{
		if (pred->a.ramp.off_nbr->pos == pred->a.ramp.prev_nbr->pos)
			return (1);
		pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
		pred->b.rev = pred->a.ramp.off_nbr;
		(*rot_pred)++;
		pred->a.ramp.sent = all->a.ramp.first_nbr;
	}
	return (0);
}
