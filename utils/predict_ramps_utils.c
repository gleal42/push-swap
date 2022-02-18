/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:22:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/18 01:41:34 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* We need:
* To have something to update the
* current b (because when we rotate the head changes)
* To keep track of the numbers we have
* already pushed (in case we need to go backwards)
*/

int	pred_other_rots(t_all *pred, t_all *all, t_lims *lims_b, t_cmds *temp_cmd)
{
	t_cmds	rot_pred;

	pred->b.near_rot.r = 0;
	pred->b.near_rot.rrev = 0;
	ft_bzero(&rot_pred, sizeof(t_cmds));
	if (pred_good_wo_rot_b(all->b.head, pred->a.head, all->b.lims));
	{
		pred_min_rots();
		return (0);
	}
	iterate_stack(&pred->b.head, all->b.head);
	all->b.rev = (pred->b.head)->prev->prev;
	while (!pred->b.near_rot.r || !pred->b.near_rot.rrev)
	{
		add_rbs(all->a.head, all->a.ramp.first_nbr, pred->a.head,
			all->b.forw, &rot_pred, lims_b);
		iterate_stack(&all->b.forw, all->b.head);
		add_rrbs(all->a.head, all->a.ramp.first_nbr, pred->a.head,
			all->b.rev, &rot_pred, lims_b);
		all->b.rev = (all->b.rev)->prev;
		check_if_found_rot(pred->a.head, &all->b, &pred->b.near_rot, all->b.lims);
	}
	calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
	if (rot_pred.rb)
		pred->b.head = all->b.forw;
	else if (rot_pred.rrb)
		pred->b.head = all->b.rev;
	update_cur_b(&rot_pred, &pred->b.head, all->b.forw, all->b.rev);
	temp_cmd->rb += rot_pred.rb;
	temp_cmd->rrb += rot_pred.rrb;
	return (0);
}

/* Continuar aqui, e talvez por pred min rots dentro desta para poupar linhas */

int		pred_good_wo_rot_b()
{
	if (!b || !b->next)
		return (1);
	if (is_next_nbr_bigger(move, b->prev, lims_b.min, lims_b.max)
		&& is_prev_nbr_smaller(move, b, lims_b.min, lims_b.max))
		return (1);
	return (0);
}

void	predict_initial_pushmoves(int closer_fwd, int closer_bwd, t_cmds *cmds)
{
	if ((cmds->rb && cmds->rb <= cmds->rrb) || !closer_bwd)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
	}
	else if ((cmds->rrb && cmds->rb > cmds->rrb) || !closer_fwd)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
	}
}