/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:07:28 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:23:30 by gleal            ###   ########.fr       */
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
	float	temp_rotates_per_push;
	float	off_rotates_per_push;

	if (!off_cmd.total)
		return (1);
	temp_rotates_per_push = temp_cmd.total / temp_cmd.pb;
	off_rotates_per_push = off_cmd.total / off_cmd.pb;
	if (temp_cmd.total < off_cmd.total)
		return (1);
	else
		return (0);
}

int	have_analyzed_enough(t_cmds off, t_rot ini_rot,
		t_elem *forw, t_elem *rev)
{
	if (off.total)
	{
		if (off.total < ini_rot.r)
			return (1);
		if (off.total < ini_rot.rrev)
			return (1);
		if (!forw)
			return (1);
		if (forw->pos == rev->pos)
			return (1);
	}
	return (0);
}

int	is_temp_better(t_cmds temp, t_cmds off)
{	
	if (!(off.total))
		return (1);
	if (temp.type == SWAP_BWD || temp.type == SWAP_FWD)
	{
		if (off.type == PUSH_B_BWD || off.type == PUSH_B_FWD)
		{
			if (temp.total < off.total + 2)
				return (1);
			else
				return (0);
		}
		else
		{
			if (temp.total < off.total)
				return (1);
			else
				return (0);
		}
	}
	if (temp.total < off.total)
		return (1);
	else
		return (0);
}
