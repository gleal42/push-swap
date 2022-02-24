/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:38:46 by gleal            ###   ########.fr       */
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

void	init_push_b(t_cmds *cmds)
{
	if (cmds->ra)
		cmds->type = PUSH_B_FWD;
	else
		cmds->type = PUSH_B_BWD;
	cmds->pb++;
	cmds->total = cmds->ra + cmds->rb
		+ cmds->rr + cmds->rra + cmds->rrb
		+ cmds->rrr + cmds->pb;
}

int	is_good_to_place_wo_rot_b(t_elem *b, t_elem *move, t_lims lims_b)
{
	if (!b || !b->next)
		return (1);
	if (is_smaller_than(move, b->prev, lims_b.min, lims_b.max)
		&& is_bigger_than(move, b, lims_b.min, lims_b.max))
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

void	check_if_found_rot(t_elem *move, t_stack *stack,
		t_rot *near_rot, t_lims lims)
{
	if (is_smaller_than(move, stack->forw->prev,
			lims.min, lims.max)
		&& is_bigger_than(move, stack->forw,
			lims.min, lims.max))
		near_rot->r++;
	if (is_smaller_than(move, stack->rev,
			lims.min, lims.max)
		&& is_bigger_than(move, stack->rev->next,
			lims.min, lims.max))
		near_rot->rrev++;
}
