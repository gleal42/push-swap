/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:30:28 by gleal             #+#    #+#             */
/*   Updated: 2022/02/24 00:12:51 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	calculate_initial_pushmoves(int closer_fwd,
	int closer_bwd, t_cmds *cmds)
{
	int	fwd_total;
	int	rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (closer_fwd)
		fwd_total = cmds->ra + cmds->rr
			+ cmds->rra + cmds->rrr + cmds->rb + cmds->pb;
	if (closer_bwd)
		rev_total = cmds->ra + cmds->rr
			+ cmds->rra + cmds->rrr + cmds->rrb + cmds->pb;
	if ((fwd_total <= rev_total && closer_fwd) || !closer_bwd)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((fwd_total > rev_total && closer_bwd) || !closer_fwd)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
}

void	find_closest_b_spot(t_elem *cur_b, t_elem *a, t_all *temp, int max)
{
	int	good_spot_forward;
	int	good_spot_reverse;
	int	rev_total;
	int	fwd_total;

	good_spot_forward = 0;
	good_spot_reverse = 0;
	fwd_total = 0;
	rev_total = 0;
	temp->pred_cmds.pa++;
	temp->pred_cmds.total = count_moves(&temp->pred_cmds);
	if (!a
		|| !a->next
		|| (is_smaller_than(cur_b, a, temp->a.lims.min, temp->a.lims.max)
			&& is_bigger_than(cur_b, a->prev,
				temp->a.lims.min, temp->a.lims.max)))
		return ;
	temp->a.forw = a->next;
	temp->a.rev = a->prev->prev;
	fwd_total = temp->pred_cmds.total;
	rev_total = temp->pred_cmds.total;
	while (!good_spot_forward && !good_spot_reverse && temp->a.forw)
	{
		if (temp->pred_cmds.rb > 0)
		{	
			temp->pred_cmds.rb--;
			temp->pred_cmds.rr++;
		}
		else
		{
			temp->pred_cmds.ra++;
			fwd_total++;
		}
		if (temp->pred_cmds.rrb > 0)
		{
			temp->pred_cmds.rrb--;
			temp->pred_cmds.rrr++;
		}
		else
		{
			temp->pred_cmds.rra++;
			rev_total++;
		}
		if (max && (fwd_total >= max && rev_total >= max))
		{
			ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
			return ;
		}
		if (is_smaller_than(cur_b, temp->a.forw,
				temp->a.lims.min, temp->a.lims.max)
			&& is_bigger_than(cur_b, temp->a.forw->prev,
				temp->a.lims.min, temp->a.lims.max))
			good_spot_forward++;
		if (temp->a.rev->next)
		{
			if (is_bigger_than(cur_b, temp->a.rev,
					temp->a.lims.min, temp->a.lims.max)
				&& is_smaller_than(cur_b, temp->a.rev->next,
					temp->a.lims.min, temp->a.lims.max))
				good_spot_reverse++;
		}
		else
		{
			if (is_bigger_than(cur_b, temp->a.rev,
					temp->a.lims.max, temp->a.lims.max)
				&& is_smaller_than(cur_b, a, temp->a.lims.min,
					temp->a.lims.max))
				good_spot_reverse++;
		}
		temp->a.rev = (temp->a.rev)->prev;
		temp->a.forw = (temp->a.forw)->next;
	}
	if (!good_spot_forward && !good_spot_reverse)
	{
		printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
		ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
		return ;
	}
	if (good_spot_forward && (fwd_total <= rev_total || !good_spot_reverse))
	{
		temp->pred_cmds.rra = 0;
		temp->pred_cmds.rrb += temp->pred_cmds.rrr;
		temp->pred_cmds.rrr = 0;
		temp->pred_cmds.total = fwd_total;
	}
	else if (good_spot_reverse
		&& (rev_total <= fwd_total || !good_spot_forward))
	{
		temp->pred_cmds.ra = 0;
		temp->pred_cmds.rb += temp->pred_cmds.rr;
		temp->pred_cmds.rr = 0;
		temp->pred_cmds.total = rev_total;
	}
}
