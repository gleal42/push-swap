/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_other_rots.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:48:29 by gleal             #+#    #+#             */
/*   Updated: 2022/02/25 21:50:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* We need:
* To have something to update the
* current b (because when we rotate the head changes)
* To keep track of the numbers we have
* already pushed (in case we need to go backwards)
*/
/*		check_if_found_rot(pred->a.head, &all->b, &pred->b.near_rot, pred->b.lims);
		iterate_fwd_rev_noend(&pred->b, all->b.head);*/

void	pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd)
{
	t_cmds	rot_pred;

	ft_bzero(&pred->b.near_rot, sizeof(t_rot));
	ft_bzero(&rot_pred, sizeof(t_cmds));
	if (!all->b.head || !all->b.head->next)
		pred_all_inirotsb(all, pred, &rot_pred);
	else
		pred_rots_multi_b(pred, all, &rot_pred);
	calculate_initial_pushmoves(rot_pred.rb <= rot_pred.rrb,
		rot_pred.rrb <= rot_pred.rb, &rot_pred);
	temp_cmd->rb += rot_pred.rb;
	temp_cmd->rrb += rot_pred.rrb;
}

void	pred_all_inirotsb(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	init_stacks_iteration(&pred->b, all->a.ramp.first_nbr);
	if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		return ;
	predict_all_ini_rbs(all, pred, rot_pred);
	predict_all_ini_rrbs(all, pred, rot_pred);
}

void	pred_rots_multi_b(t_all *pred, t_all *all, t_cmds *rot_pred)
{
	t_elem	*target_fwd;
	t_elem	*target_bwd;

	init_stacks_iteration(&pred->b, pred->a.head);
	target_fwd = pred->b.head;
	target_bwd = pred->b.head->prev;
	while (pred->b.forw->pos != pred->a.head->pos
		|| pred->b.rev->pos != pred->a.head->pos)
	{
		if (pred->b.forw->pos != pred->a.head->pos)
		{
			if (target_fwd->pos != pred->b.head->pos)
				rot_pred->rb++;
			add_rbs(all, pred, &target_fwd, rot_pred);
		}
		if (pred->b.rev->pos != pred->a.head->pos)
		{
			rot_pred->rrb++;
			add_rrbs(all, pred, &target_bwd, rot_pred);
		}
		if (rot_pred->rb <= rot_pred->rrb)
			pred->b.head = target_fwd;
		else
			pred->b.head = target_bwd;
	}
}
