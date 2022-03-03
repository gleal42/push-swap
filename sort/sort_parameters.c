/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:07:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/03 02:57:08 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*  
* See which is best metric for every size of ramp
*/

/* 
	if (all->a.ramp.init_cmds.total < all->a.ramp.best_cmds.total)

	if (temp_cmd.total/temp_cmd.pb < off_cmd.total/off_cmd.pb)
	if (temp_avg_cmds < off_avg_cmds)
 */

// if (is_better_ramp(all, all->a.ramp.init_cmds, all->a.ramp.best_cmds, all->a.ramp.first_nbr, firstinramp))

int	is_better_ramp(t_all *all, t_elem *firstinramp)
{
	float	temp_avg_cmds;
	float	off_avg_cmds;

	update_ramp_size(all, all->a.ramp.first_nbr->prev, firstinramp, &all->a.ramp.init_cmds.ramp_size);
	if (!all->a.ramp.best_cmds.total)
		return (1);
	if (all->a.ramp.init_cmds.ramp_size == 0) 
		temp_avg_cmds = all->a.ramp.init_cmds.total;
	else
		temp_avg_cmds = all->a.ramp.init_cmds.total 
						* (all->a.ramp.init_cmds.pb/all->a.ramp.init_cmds.ramp_size);
	off_avg_cmds = all->a.ramp.best_cmds.total 
					* (all->a.ramp.best_cmds.pb/all->a.ramp.best_cmds.ramp_size);
	if (all->a.ramp.init_cmds.total < all->a.ramp.best_cmds.total)
		return (1);
	else
		return (0);
}

void	update_ramp_size(t_all	*all, t_elem *fst_rmp,  t_elem *sec_rmp, int	*size)
{
	*size = 0;
	while (is_smaller_than(fst_rmp->prev, fst_rmp, all->a.lims.min, all->a.lims.max))
	{
		fst_rmp = fst_rmp->prev;
		(*size)++;
	}
	while (is_smaller_than(sec_rmp, fst_rmp, all->a.lims.min, all->a.lims.max))
	{
		iterate_stack(&sec_rmp, all->a.head);
		(*size)++;
	}
}

/* 
	if ((all->a.ramp.first_nbr->prev)->pos == firstinramp->pos)
	if (is_smaller_than(all->a.ramp.first_nbr->prev, all->a.ramp.first_nbr, all->a.lims.min, all->a.lims.max))
*/
int	stop_pred_ramps(t_all *all, t_elem *firstinramp)
{
	(void)firstinramp;
	t_elem	*next_el;

	next_el = next_elem(all->a.ramp.first_nbr, all->a.head);
	if (is_bigger_than(all->a.ramp.first_nbr, next_el, all->a.lims.min, all->a.lims.max))
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
