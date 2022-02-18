/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:30:28 by gleal             #+#    #+#             */
/*   Updated: 2022/02/18 17:01:47 by gleal            ###   ########.fr       */
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

void	find_closest_b_spot(t_elem *cur_b, t_elem *a, t_all *all, int max)
{
	int	good_spot_forward;
	int	good_spot_reverse;
	int	rev_total;
	int	fwd_total;

	ft_bzero(&all->pred_cmds, sizeof(t_cmds));
	good_spot_forward = 0;
	good_spot_reverse = 0;
	fwd_total = 0;
	rev_total = 0;
	all->pred_cmds.rb = all->b.ini_rot.r;
	all->pred_cmds.rrb = all->b.ini_rot.rrev;
	all->pred_cmds.pa++;
	all->pred_cmds.total = count_moves(&all->pred_cmds);
	if (!a)
		return ;
	if (!a->next)
	{
		if (cur_b->nbr > a->nbr)
		{
			good_spot_forward++;
			all->pred_cmds.ra++;
		}
		else
			good_spot_reverse++;
	}
	if (is_smaller_than(cur_b, a, all->a.lims.min, all->a.lims.max)
		&& is_bigger_than(cur_b, a->prev,
			all->a.lims.min, all->a.lims.max))
		return ;
	all->a.forw = a->next;
	all->a.rev = a->prev->prev;
	fwd_total = all->pred_cmds.total;
	rev_total = all->pred_cmds.total;
	while (!good_spot_forward && !good_spot_reverse && all->a.forw)
	{
		if (all->pred_cmds.rb > 0)
		{	
			all->pred_cmds.rb--;
			all->pred_cmds.rr++;
		}
		else
		{
			all->pred_cmds.ra++;
			fwd_total++;
		}
		if (all->pred_cmds.rrb > 0)
		{
			all->pred_cmds.rrb--;
			all->pred_cmds.rrr++;
		}
		else
		{
			all->pred_cmds.rra++;
			rev_total++;
		}
		if (max && (fwd_total >= max && rev_total >= max))
		{
			ft_bzero(&all->pred_cmds, sizeof(t_cmds));
			return ;
		}
		if (is_smaller_than(cur_b, all->a.forw,
				all->a.lims.min, all->a.lims.max)
			&& is_bigger_than(cur_b, all->a.forw->prev,
				all->a.lims.min, all->a.lims.max))
			good_spot_forward++;
		if (all->a.rev->next)
		{
			if (is_bigger_than(cur_b, all->a.rev,
					all->a.lims.min, all->a.lims.max)
				&& is_smaller_than(cur_b, all->a.rev->next,
					all->a.lims.max, all->a.lims.max))
				good_spot_reverse++;
		}
		else
		{
			if (is_bigger_than(cur_b, all->a.rev,
					all->a.lims.max, all->a.lims.max)
				&& is_smaller_than(cur_b, a, all->a.lims.min,
					all->a.lims.max))
				good_spot_reverse++;
		}
		all->a.rev = (all->a.rev)->prev;
		all->a.forw = (all->a.forw)->next;
	}
	if (!good_spot_forward && !good_spot_reverse)
	{
		printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
		ft_bzero(&all->pred_cmds, sizeof(t_cmds));
		return ;
	}
	if (good_spot_forward && (fwd_total <= rev_total || !good_spot_reverse))
	{
		all->pred_cmds.rra = 0;
		all->pred_cmds.rrb += all->pred_cmds.rrr;
		all->pred_cmds.rrr = 0;
		all->pred_cmds.total = fwd_total;
	}
	else if (good_spot_reverse
		&& (rev_total <= fwd_total || !good_spot_forward))
	{
		all->pred_cmds.ra = 0;
		all->pred_cmds.rb += all->pred_cmds.rr;
		all->pred_cmds.rr = 0;
		all->pred_cmds.total = rev_total;
	}
}