/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 23:32:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	not_rotate_fwd(t_cmds *cmds)
{
	if (cmds->ra)
		cmds->ra--;
	else if (cmds->rra || !cmds->ra)
		cmds->rra++;
}

void	init_push_b(t_all *temp)
{
	if (temp->exec_cmds.ra)
		temp->exec_cmds.type = PUSH_B_FWD;
	else
		temp->exec_cmds.type = PUSH_B_BWD;
	temp->exec_cmds.pb++;
	temp->exec_cmds.total = temp->exec_cmds.ra + temp->exec_cmds.rb
		+ temp->exec_cmds.rr + temp->exec_cmds.rra + temp->exec_cmds.rrb
		+ temp->exec_cmds.rrr + temp->exec_cmds.pb;
}

int	is_good_to_place_no_rot_b(t_elem *b, t_elem *tobemoved, t_limits lims_b)
{
	if (!b || !b->next)
		return (1);
	if (is_next_nbr_bigger(tobemoved, b->prev, lims_b.min, lims_b.max)
		&& is_prev_nbr_smaller(tobemoved, b, lims_b.min, lims_b.max))
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

void	check_if_found_rot(t_all *temp, t_elem *tobemoved, int *fwd, int *bwd)
{
	if (is_next_nbr_bigger(tobemoved, temp->b.forw->prev,
			temp->b.lims.min, temp->b.lims.max)
		&& is_prev_nbr_smaller(tobemoved, temp->b.forw,
			temp->b.lims.min, temp->b.lims.max))
		(*fwd)++;
	if (is_next_nbr_bigger(tobemoved, temp->b.rev,
			temp->b.lims.min, temp->b.lims.max)
		&& is_prev_nbr_smaller(tobemoved, temp->b.rev->next,
			temp->b.lims.min, temp->b.lims.max))
		(*bwd)++;
}