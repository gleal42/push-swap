/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_a_b_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:12:44 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:21:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	analyze_fwd(t_all **all)
{
	if (is_smaller_than((*all)->a.forw, ((*all)->a.forw)->next,
			(*all)->a.lims.min, (*all)->a.lims.max))
		(*all)->a.ini_rot.r++;
	else
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, (*all)->a.forw, (*all)->a.lims.min,
				(*all)->a.lims.max))
		{
			(*all)->pred_cmds.ra = (*all)->a.ini_rot.r;
			swap_a(*all, (*all)->a.head);
			(*all)->a.ini_rot.r++;
		}
		else
		{
			(*all)->a.ini_rot.r++;
			(*all)->pred_cmds.ra = (*all)->a.ini_rot.r;
			merge_ramp_spot(*all, (*all)->a.forw->next);
		}
		if (is_temp_better((*all)->pred_cmds, (*all)->exec_cmds))
			(*all)->exec_cmds = (*all)->pred_cmds;
	}
	(*all)->a.forw = (*all)->a.forw->next;
}

void	analyze_bwd(t_all **all)
{
	if (is_bigger_than((*all)->a.rev, (*all)->a.rev->prev,
			(*all)->a.lims.min, (*all)->a.lims.max))
		(*all)->a.ini_rot.rrev++;
	else
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, (*all)->a.rev->prev,
				(*all)->a.lims.min, (*all)->a.lims.max))
		{
			(*all)->a.ini_rot.rrev++;
			(*all)->pred_cmds.rra = (*all)->a.ini_rot.rrev;
			swap_a(*all, (*all)->a.head);
		}
		else
		{
			(*all)->pred_cmds.rra = (*all)->a.ini_rot.rrev;
			merge_ramp_spot(*all, (*all)->a.rev);
			(*all)->a.ini_rot.rrev++;
		}
		if (is_temp_better((*all)->pred_cmds, (*all)->exec_cmds))
			(*all)->exec_cmds = (*all)->pred_cmds;
	}
	(*all)->a.rev = (*all)->a.rev->prev;
}
