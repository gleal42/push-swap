/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/18 01:21:54 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ramp_start_before(t_cmds *cmds)
{
	if (cmds->ra)
		cmds->ra--;
	else if (cmds->rra || !cmds->ra)
		cmds->rra++;
}

void	init_push_b(t_all *all)
{
	if (all->pred_cmds.ra)
		all->pred_cmds.type = PUSH_B_FWD;
	else
		all->pred_cmds.type = PUSH_B_BWD;
	all->pred_cmds.pb++;
	all->pred_cmds.total = all->pred_cmds.ra + all->pred_cmds.rb
		+ all->pred_cmds.rr + all->pred_cmds.rra + all->pred_cmds.rrb
		+ all->pred_cmds.rrr + all->pred_cmds.pb;
}

int	is_good_to_place_wo_rot_b(t_elem *b, t_elem *move, t_lims lims_b)
{
	if (!b || !b->next)
		return (1);
	if (is_next_nbr_bigger(move, b->prev, lims_b.min, lims_b.max)
		&& is_prev_nbr_smaller(move, b, lims_b.min, lims_b.max))
		return (1);
	return (0);
}

void	add_double_rots_a(t_cmds *cmds)
{
	if (cmds->ra > 0)
	{
		cmds->ra--;
		cmds->rr++;
	}
	else
		cmds->rb++;
	if (cmds->rra > 0)
	{
		cmds->rra--;
		cmds->rrr++;
	}
	else
		cmds->rrb++;
}

void	check_if_found_rot(t_elem *move, t_stack *stack, t_rot *near_rot, t_lims lims)
{
	if (is_next_nbr_bigger(move, stack->forw->prev,
			lims.min, lims.max)
		&& is_prev_nbr_smaller(move, stack->forw,
			lims.min, lims.max))
		near_rot->r++;
	if (is_next_nbr_bigger(move, stack->rev,
			lims.min, lims.max)
		&& is_prev_nbr_smaller(move, stack->rev->next,
			lims.min, lims.max))
		near_rot->rrev++;
}