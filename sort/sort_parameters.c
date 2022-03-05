/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:07:28 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 18:37:43 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

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

int	is_temp_better(t_all *all)
{
	if (!all->exec_cmds.total)
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
	if (all->pred_cmds.total && (all->pred_cmds.total < all->exec_cmds.total))
		return (1);
	else
		return (0);
}
