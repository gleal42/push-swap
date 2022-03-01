/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_other_rots.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:55:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 19:55:11 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

void	pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd)
{
	t_cmds	rot_pred;

	ft_bzero(&pred->b.near_rot, sizeof(t_rot));
	ft_bzero(&rot_pred, sizeof(t_cmds));
	if (!all->b.head || !all->b.head->next)
		pred_all_inirotsb(all, pred, &rot_pred);
	else
		pred_rots_multi_b(pred, all, &rot_pred);
	calculate_initial_pb_moves((rot_pred.rb && (rot_pred.rb <= rot_pred.rrb)),
		rot_pred.rrb && (rot_pred.rrb <= rot_pred.rb), &rot_pred);
	temp_cmd->rb += rot_pred.rb;
	temp_cmd->rrb += rot_pred.rrb;
}

void	pred_all_inirotsb(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	init_stacks_iteration(&pred->b, pred->a.head->prev);
	if (pred->a.head->prev->pos == all->a.ramp.first_nbr->pos)
	{
		if (pred->a.head->pos > pred->a.head->prev->pos)
			rot_pred->rb++;
		return ;
	}
	predict_all_ini_rbs(all, pred, rot_pred);
	predict_all_ini_rrbs(all, pred, rot_pred);
}

//ver porque est]a mal o pred->b.head em vez do pred.a.head

void	pred_rots_multi_b(t_all *pred, t_all *all, t_cmds *rot_pred)
{
	init_stacks_iteration(&pred->b, pred->a.head->prev);
	pred->b.fwd.target = pred->b.head;
	pred->b.bwd.target = pred->b.head->prev;
	while (pred->b.forw->pos != pred->a.head->pos
		|| pred->b.rev->pos != pred->a.head->pos)
	{
		if (pred->b.forw->pos != pred->a.head->pos)
			add_rbs(all, pred, &pred->b.fwd.target, rot_pred);
		if (pred->b.rev->pos != pred->a.head->pos)
			add_rrbs(all, pred, &pred->b.bwd.target, rot_pred);
	}
	if ((!rot_pred->rb && !rot_pred->rrb) || (rot_pred->rb <= rot_pred->rrb))
		pred->b.head = pred->b.fwd.target;
	else
	{
		iterate_stack(&pred->b.bwd.target, all->b.head);
		pred->b.head = pred->b.bwd.target;
	}
}
