/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:11:18 by gleal             #+#    #+#             */
/*   Updated: 2022/02/07 00:31:13 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	find_closest_b_spot(t_stack *cur_b, t_stack *a, t_all *temp, int max)
{
	int	good_spot_forward;
	int	good_spot_reverse;
	int	rev_total;
	int	fwd_total;

	init_cmd_list(&temp->cmds);
	good_spot_forward = 0;
	good_spot_reverse = 0;
	fwd_total = 0;
	rev_total = 0;
	temp->cmds.rb = temp->ini_rot_b.rb;
	temp->cmds.rrb = temp->ini_rot_b.rrb;
	temp->cmds.pa++;
	temp->cmds.total = count_moves(&temp->cmds);
	if (!a)
		return ;
	if (!a->next)
	{
		if (cur_b->nbr > a->nbr)
		{
			good_spot_forward++;
			temp->cmds.ra++;
		}
		else
			good_spot_reverse++;
	}
	if (is_next_nbr_bigger(cur_b, a, temp->lims.min_a, temp->lims.max_a)
		&& is_prev_nbr_smaller(cur_b, a->prev, temp->lims.min_a, temp->lims.max_a))
		return ;
	temp->forw_a = a->next;
	temp->rev_a = a->prev->prev;
	fwd_total = temp->cmds.total;
	rev_total = temp->cmds.total;
	while (!good_spot_forward && !good_spot_reverse && temp->forw_a)
	{
		if (temp->cmds.rb > 0)
		{	
			temp->cmds.rb--;
			temp->cmds.rr++;
		}
		else
		{
			temp->cmds.ra++;
			fwd_total++;
		}
		if (temp->cmds.rrb > 0)
		{
			temp->cmds.rrb--;
			temp->cmds.rrr++;
		}
		else
		{
			temp->cmds.rra++;
			rev_total++;
		}
		if (max && (fwd_total >= max && rev_total >= max))
		{
			init_cmd_list(&temp->cmds);
			return ;
		}
		if (is_next_nbr_bigger(cur_b, temp->forw_a,
				temp->lims.min_a, temp->lims.max_a)
			&& is_prev_nbr_smaller(cur_b, temp->forw_a->prev,
					temp->lims.min_a, temp->lims.max_a))
			good_spot_forward++;
		if (temp->rev_a->next)
		{
			if (is_prev_nbr_smaller(cur_b, temp->rev_a,
					temp->lims.min_a, temp->lims.max_a)
				&& is_next_nbr_bigger(cur_b, temp->rev_a->next,
						temp->lims.min_a, temp->lims.max_a))
				good_spot_reverse++;
		}
		else
		{
			if (is_prev_nbr_smaller(cur_b, temp->rev_a,
					temp->lims.min_a, temp->lims.max_a)
				&& is_next_nbr_bigger(cur_b, a, temp->lims.min_a,
						temp->lims.max_a))
				good_spot_reverse++;
		}
		temp->rev_a = (temp->rev_a)->prev;
		temp->forw_a = (temp->forw_a)->next;
	}
	if (!good_spot_forward && !good_spot_reverse)
	{
		printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
		init_cmd_list(&temp->cmds);
		return ;
	}
	if (good_spot_forward && (fwd_total <= rev_total || !good_spot_reverse))
	{
		temp->cmds.rra = 0;
		temp->cmds.rrb = temp->cmds.rrr;
		temp->cmds.rrr = 0;
		temp->cmds.total = fwd_total;
	}
	else if (good_spot_reverse
		&& (rev_total <= fwd_total || !good_spot_reverse))
	{
		temp->cmds.ra = 0;
		temp->cmds.rb = temp->cmds.rr;
		temp->cmds.rr = 0;
		temp->cmds.total = rev_total;
	}
}

void	predict_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds)
{
	if ((cmds->rb && cmds->rb <= cmds->rrb) || !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
	}
	else if ((cmds->rrb && cmds->rb > cmds->rrb) || !has_rb)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
	}
}

void	calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds)
{
	int	fwd_total;
	int	rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (has_rb)
		fwd_total = cmds->ra + cmds->rr + cmds->rra + cmds->rrr + cmds->rb + cmds->pb;
	if (has_rrb)
		rev_total = cmds->ra + cmds->rr + cmds->rra + cmds->rrr + cmds->rrb + cmds->pb;
	if ((fwd_total <= rev_total && has_rb) || !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((fwd_total > rev_total && has_rrb) || !has_rb)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
}
