/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:07:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/02 23:49:56 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*  
* See which is best metric for every size of ramp
*/

/* 
	if (temp_cmd.total < off_cmd.total)
	if (temp_cmd.total/temp_cmd.pb < off_cmd.total/off_cmd.pb)
 */

int	is_better_ramp(t_cmds temp_cmd, t_cmds off_cmd)
{
	float	temp_avg_cmds;
	float	off_avg_cmds;

	if (!off_cmd.total)
		return (1);
	temp_avg_cmds = temp_cmd.total/temp_cmd.pb;
	off_avg_cmds = off_cmd.total/off_cmd.pb;
	if (temp_avg_cmds < off_avg_cmds)
		return (1);
	else
		return (0);
}

/* 
	if ((all->a.ramp.first_nbr->prev)->pos == firstinramp->pos)
	if (is_smaller_than(all->a.ramp.first_nbr->prev, all->a.ramp.first_nbr, all->a.lims.min, all->a.lims.max))
*/
int	stop_pred_ramps(t_all *all, t_elem *firstinramp)
{
	(void)firstinramp;
	if (is_smaller_than(all->a.ramp.first_nbr->prev, all->a.ramp.first_nbr, all->a.lims.min, all->a.lims.max))
		return (1);
	return (0);
}

// if (all->exec_cmds.total < all->a.ini_rot.r)
// 	return (1);
// if (all->exec_cmds.total < all->a.ini_rot.rrev)
// 	return (1);

int	have_analyzed_enough(t_all *all)
{
	if (all->exec_cmds.total)
	{
		if (all_number_checked(all))
			return (1);
	}
	return (0);
}

/* 	
	if (all->a.ramp.best_cmds.total < all->ramp_cmds.total)
	if (all->pred_cmds.total < all->exec_cmds.total)
	if (temp_avg_cmds < off_avg_cmds)
*/

int	is_temp_better(t_all *all)
{
	float	temp_avg_cmds;
	float	off_avg_cmds;

	if (!all->exec_cmds.total)
		return (1);
	temp_avg_cmds = all->a.ramp.best_cmds.total/all->a.ramp.best_cmds.pb;
	off_avg_cmds = all->ramp_cmds.total/all->ramp_cmds.pb;
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
	if (all->pred_cmds.total < all->exec_cmds.total)
		return (1);
	else
		return (0);
}
