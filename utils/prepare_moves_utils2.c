/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:30:28 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 16:21:03 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	calculate_initial_pushmoves(int closer_fwd, int closer_bwd, t_cmds *cmds)
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

	ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
	good_spot_forward = 0;
	good_spot_reverse = 0;
	fwd_total = 0;
	rev_total = 0;
	temp->exec_cmds.rb = temp->b.ini_rot.r;
	temp->exec_cmds.rrb = temp->b.ini_rot.rrev;
	temp->exec_cmds.pa++;
	temp->exec_cmds.total = count_moves(&temp->exec_cmds);
	if (!a)
		return ;
	if (!a->next)
	{
		if (cur_b->nbr > a->nbr)
		{
			good_spot_forward++;
			temp->exec_cmds.ra++;
		}
		else
			good_spot_reverse++;
	}
	if (is_next_nbr_bigger(cur_b, a, temp->a.lims.min, temp->a.lims.max)
		&& is_prev_nbr_smaller(cur_b, a->prev,
			temp->a.lims.min, temp->a.lims.max))
		return ;
	temp->a.forw = a->next;
	temp->a.rev = a->prev->prev;
	fwd_total = temp->exec_cmds.total;
	rev_total = temp->exec_cmds.total;
	while (!good_spot_forward && !good_spot_reverse && temp->a.forw)
	{
		if (temp->exec_cmds.rb > 0)
		{	
			temp->exec_cmds.rb--;
			temp->exec_cmds.rr++;
		}
		else
		{
			temp->exec_cmds.ra++;
			fwd_total++;
		}
		if (temp->exec_cmds.rrb > 0)
		{
			temp->exec_cmds.rrb--;
			temp->exec_cmds.rrr++;
		}
		else
		{
			temp->exec_cmds.rra++;
			rev_total++;
		}
		if (max && (fwd_total >= max && rev_total >= max))
		{
			ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
			return ;
		}
		if (is_next_nbr_bigger(cur_b, temp->a.forw,
				temp->a.lims.min, temp->a.lims.max)
			&& is_prev_nbr_smaller(cur_b, temp->a.forw->prev,
				temp->a.lims.min, temp->a.lims.max))
			good_spot_forward++;
		if (temp->a.rev->next)
		{
			if (is_prev_nbr_smaller(cur_b, temp->a.rev,
					temp->a.lims.min, temp->a.lims.max)
				&& is_next_nbr_bigger(cur_b, temp->a.rev->next,
					temp->a.lims.max, temp->a.lims.max))
				good_spot_reverse++;
		}
		else
		{
			if (is_prev_nbr_smaller(cur_b, temp->a.rev,
					temp->a.lims.max, temp->a.lims.max)
				&& is_next_nbr_bigger(cur_b, a, temp->a.lims.min,
					temp->a.lims.max))
				good_spot_reverse++;
		}
		temp->a.rev = (temp->a.rev)->prev;
		temp->a.forw = (temp->a.forw)->next;
	}
	if (!good_spot_forward && !good_spot_reverse)
	{
		printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		return ;
	}
	if (good_spot_forward && (fwd_total <= rev_total || !good_spot_reverse))
	{
		temp->exec_cmds.rra = 0;
		temp->exec_cmds.rrb += temp->exec_cmds.rrr;
		temp->exec_cmds.rrr = 0;
		temp->exec_cmds.total = fwd_total;
	}
	else if (good_spot_reverse
		&& (rev_total <= fwd_total || !good_spot_forward))
	{
		temp->exec_cmds.ra = 0;
		temp->exec_cmds.rb += temp->exec_cmds.rr;
		temp->exec_cmds.rr = 0;
		temp->exec_cmds.total = rev_total;
	}
}