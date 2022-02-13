/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:34:05 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 17:13:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	find_rotation_direction(t_all *all, int *rotation_direction)
{
	while (!(*rotation_direction) && all->a.forw)
	{
		if (all->a.forw->pos == 1)
			(*rotation_direction) = RA;
		else if (all->a.rev->pos == 1)
			(*rotation_direction) = RRA;
		if (all->a.forw->pos == all->a.rev->pos)
			break ;
		all->a.forw = all->a.forw->next;
		if (all->a.forw->pos == all->a.rev->pos)
			break ;
		all->a.rev = all->a.rev->prev;
	}
	if (!(*rotation_direction))
		return ;
}

void	analyze_fwd(t_all **all, t_all *temp)
{
	if (is_next_nbr_bigger(temp->a.forw, (temp->a.forw)->next,
			temp->a.lims.min, temp->a.lims.max))
	{
		temp->a.ini_rot.r++;
		temp->a.forw = temp->a.forw->next;
	}
	else
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, temp->a.forw, temp->a.lims.min,
				temp->a.lims.max))
		{
			temp->exec_cmds.ra = temp->a.ini_rot.r;
			swap_a(temp, temp->a.forw, (*all)->a.head);
			temp->a.ini_rot.r++;
		}
		else
		{
			temp->a.ini_rot.r++;
			temp->exec_cmds.ra = temp->a.ini_rot.r;
			merge_ramp_spot(*all, temp, temp->a.forw->next);
		}
		if (is_temp_better(temp->exec_cmds, (*all)->exec_cmds))
			(*all)->exec_cmds = temp->exec_cmds;
		temp->a.forw = temp->a.forw->next;
	}
}

void	analyze_bwd(t_all **all, t_all *temp)
{
	if (is_prev_nbr_smaller(temp->a.rev, temp->a.rev->prev,
			temp->a.lims.min, temp->a.lims.max))
	{
		temp->a.ini_rot.rrev++;
		temp->a.rev = temp->a.rev->prev;
	}
	else
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, temp->a.rev->prev,
				temp->a.lims.min, temp->a.lims.max))
		{
			temp->a.ini_rot.rrev++;
			temp->exec_cmds.rra = temp->a.ini_rot.rrev;
			swap_a(temp, temp->a.rev->prev, (*all)->a.head);
		}
		else
		{
			temp->exec_cmds.rra = temp->a.ini_rot.rrev;
			merge_ramp_spot(*all, temp, temp->a.rev);
			temp->a.ini_rot.rrev++;
		}
		if (is_temp_better(temp->exec_cmds, (*all)->exec_cmds))
			(*all)->exec_cmds = temp->exec_cmds;
		temp->a.rev = temp->a.rev->prev;
	}
}
