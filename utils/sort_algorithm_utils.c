/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:01:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/10 14:52:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	find_rotation_direction(t_all *all, int *rotation_direction)
{
	while (!(*rotation_direction) && all->forw_a)
	{
		if (all->forw_a->pos == 1)
			(*rotation_direction) = RA;
		else if (all->rev_a->pos == 1)
			(*rotation_direction) = RRA;
		if (all->forw_a->pos == all->rev_a->pos)
			break ;
		all->forw_a = all->forw_a->next;
		if (all->forw_a->pos == all->rev_a->pos)
			break ;
		all->rev_a = all->rev_a->prev;
	}
	if (!(*rotation_direction))
		return ;
}
void	analyze_fwd(t_all **all, t_all *temp)
{
	if (is_next_nbr_bigger(temp->forw_a, (temp->forw_a)->next,
			temp->lims.min_a, temp->lims.max_a))
	{
		temp->ini_rot_a.ra++;
		temp->forw_a = temp->forw_a->next;
	}
	else
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a, temp->forw_a, temp->lims.min_a,
				temp->lims.max_a))
		{
			temp->exec_cmds.ra = temp->ini_rot_a.ra;
			swap_a(temp, temp->forw_a, (*all)->a);
			temp->ini_rot_a.ra++;
		}
		else
		{
			temp->ini_rot_a.ra++;
			temp->exec_cmds.ra = temp->ini_rot_a.ra;
			merge_ramp_spot((*all)->a, (*all)->b, temp, temp->forw_a->next);
		}
		if (is_temp_better(temp->exec_cmds, (*all)->exec_cmds))
			(*all)->exec_cmds = temp->exec_cmds;
		temp->forw_a = temp->forw_a->next;
	}
}


void	analyze_bwd(t_all **all, t_all *temp)
{
	if (is_prev_nbr_smaller(temp->rev_a, temp->rev_a->prev,
			temp->lims.min_a, temp->lims.max_a))
	{
		temp->ini_rot_a.rra++;
		temp->rev_a = temp->rev_a->prev;
	}
	else
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a, temp->rev_a->prev,
				temp->lims.min_a, temp->lims.max_a))
		{
			temp->ini_rot_a.rra++;
			temp->exec_cmds.rra = temp->ini_rot_a.rra;
			swap_a(temp, temp->rev_a->prev, (*all)->a);
		}
		else
		{
			temp->exec_cmds.rra = temp->ini_rot_a.rra;
			merge_ramp_spot((*all)->a, (*all)->b, temp, temp->rev_a);
			temp->ini_rot_a.rra++;
		}
		if (is_temp_better(temp->exec_cmds, (*all)->exec_cmds))
			(*all)->exec_cmds = temp->exec_cmds;
		temp->rev_a = temp->rev_a->prev;
	}
}