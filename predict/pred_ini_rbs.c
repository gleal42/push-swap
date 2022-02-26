/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_ini_rots.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:08:02 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 21:08:04 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	pred->a.ramp.sent = all->a.ramp.first_nbr;
	pred->a.ramp.off_nbr = pred->a.ramp.sent;
	pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
	iterate_stack(&pred->a.ramp.sent, all->a.head);
	if (pred->a.ramp.sent->pos == pred->a.head->pos)
		return ;
	pred->a.ramp.sent = all->a.ramp.first_nbr;
	pred->b.forw = pred->a.ramp.sent;
	while (pred->b.forw->pos != pred->a.head->pos)
	{
		iterate_stack(&pred->a.ramp.sent, all->a.head);
		predict_next_ini_rb_nbr(pred);
		if (update_pred_rbs_reset(all, pred, &rot_pred->rb))
			break ;
	}
}

void	predict_next_ini_rb_nbr(t_all *pred)
{
	if (is_bigger_than(pred->b.forw, pred->a.ramp.sent,
			pred->b.lims.min, pred->b.lims.max)
		&& (pred->a.ramp.sent->pos >= pred->a.ramp.off_nbr->pos))
		pred->a.ramp.off_nbr = pred->a.ramp.sent;
}

int	update_pred_rbs_reset(t_all *all, t_all *pred, int *rot_pred)
{
	if (pred->a.ramp.sent->pos == pred->a.head->pos)
	{
		if (pred->a.ramp.off_nbr->pos == pred->a.ramp.prev_nbr->pos)
			return (1);
		pred->a.ramp.prev_nbr = pred->a.ramp.off_nbr;
		pred->b.forw = pred->a.ramp.off_nbr;
		(*rot_pred)++;
		pred->a.ramp.sent = all->a.ramp.first_nbr;
	}
	return (0);
}
