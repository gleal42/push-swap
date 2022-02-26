/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:30:28 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:19:31 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

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

void	add_double_rots_b(t_cmds *cmds, int	*fwd_total, int *rev_total)
{
	if (cmds->rb > 0)
	{
		cmds->rb--;
		cmds->rr++;
	}
	else
	{
		cmds->ra++;
		(*fwd_total)++;
	}
	if (cmds->rrb > 0)
	{
		cmds->rrb--;
		cmds->rrr++;
	}
	else
	{
		cmds->rra++;
		(*rev_total)++;
	}
}

void	calculate_initial_pb_moves(int best_fwd, int best_bwd, t_cmds *cmds)
{
	int	fwd_total;
	int	rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (best_fwd)
		fwd_total = cmds->ra + cmds->rra + cmds->rr
			+ cmds->rb + cmds->rrr + cmds->pb;
	if (best_bwd)
		rev_total = cmds->ra + cmds->rra + cmds->rr
			+ cmds->rrb + cmds->rrr + cmds->pb;
	if ((fwd_total <= rev_total && best_fwd) || !best_bwd)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((fwd_total > rev_total && best_bwd) || !best_fwd)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
}

void	calculate_initial_pa_moves(int best_fwd, int best_bwd, t_cmds *cmds)
{
	int	fwd_total;
	int	rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (best_fwd)
		fwd_total = cmds->ra + cmds->rr
			+ cmds->rb + cmds->rrb + cmds->rrr + cmds->pb;
	if (best_bwd)
		rev_total = cmds->rra + cmds->rr
			+ cmds->rb + cmds->rrb + cmds->rrr + cmds->pb;
	if ((fwd_total <= rev_total && best_fwd) || !best_bwd)
	{
		cmds->rra = 0;
		cmds->rrb += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((fwd_total > rev_total && best_bwd) || !best_fwd)
	{
		cmds->ra = 0;
		cmds->rb += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
}

void	ramp_start_before(t_cmds *cmds)
{
	if (cmds->ra)
		cmds->ra--;
	else if (cmds->rra || !cmds->ra)
		cmds->rra++;
}
