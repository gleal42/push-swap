/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:07:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/02 02:17:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*  
* See which is best metric for every size of ramp
*/
/* temp_rotates_per_push = (temp_cmd.rb + temp_cmd.rrb)/temp_cmd.pb;
off_ratio = (off_cmd.rb + off_cmd.rrb)/off_cmd.pb;
if (temp_ratio < off_ratio)
if (temp_cmd.total < off_cmd.total && temp_rotates_per_push
< off_rotates_per_push) */

int	is_better_ramp(t_cmds temp_cmd, t_cmds off_cmd)
{
	if (!off_cmd.total)
		return (1);
	if (temp_cmd.total < off_cmd.total)
		return (1);
	else
		return (0);
}
// all->exec_cmds, all->a.ini_rot, all->a.forw, all->a.rev

int	have_analyzed_enough(t_all *all)
{
	if (all->exec_cmds.total)
	{
		if (all->exec_cmds.total < all->a.ini_rot.r)
			return (1);
		if (all->exec_cmds.total < all->a.ini_rot.rrev)
			return (1);
		if (all_number_checked(all))
			return (1);
	}
	return (0);
}

int	all_number_checked(t_all *all)
{
	if (!all->a.forw)
		return (1);
	if (all->a.forw->pos == all->a.rev->pos)
		return (1);
	if (all->a.forw->prev->pos == all->a.rev->pos)
		return (1);
	return (0);
}

// (*all)->pred_cmds, all->exec_cmds, all->ramp_cmds, all->a.ramp.best_cmds
	// if (all->pred_cmds.total < all->exec_cmds.total)
	// if (all->a.ramp.best_cmds.total < all->ramp_cmds.total)

int	is_temp_better(t_all *all)
{	
	if (!(all->exec_cmds.total))
		return (1);
	if (all->pred_cmds.type == SWAP_BWD || all->pred_cmds.type == SWAP_FWD)
	{
		if (all->exec_cmds.type == PUSH_B_BWD
			|| all->exec_cmds.type == PUSH_B_FWD)
		{
			if (all->pred_cmds.total < all->exec_cmds.total + 2)
				return (1);
			else
				return (0);
		}
		else
		{
			if (all->pred_cmds.total < all->exec_cmds.total)
				return (1);
			else
				return (0);
		}
	}
	if (all->a.ramp.best_cmds.total < all->ramp_cmds.total)
		return (1);
	else
		return (0);
}
