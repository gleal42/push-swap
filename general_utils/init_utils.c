/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:45:45 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:40:13 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	init_all(t_all *temp, t_all *all, int n)
{
	init_rots(all);
	init_lims(all, n);
	ft_bzero(&all->pred_cmds, sizeof(t_cmds));
	ft_bzero(&all->exec_cmds, sizeof(t_cmds));
	init_stacks_iteration(&all->a, all->a.head);
	*temp = *all;
}

void	init_rots(t_all *all)
{
	ft_bzero(&all->a.ini_rot, sizeof(t_rot));
	ft_bzero(&all->b.ini_rot, sizeof(t_rot));
}

void	init_lims(t_all *all, int n)
{
	all->a.lims.min = 1;
	all->a.lims.max = n;
	all->b.lims.min = 0;
	all->b.lims.max = 0;
}

void	init_push_b(t_cmds *cmds)
{
	if (cmds->ra)
		cmds->type = PUSH_B_FWD;
	else
		cmds->type = PUSH_B_BWD;
	cmds->total = cmds->ra + cmds->rb
		+ cmds->rr + cmds->rra + cmds->rrb
		+ cmds->rrr + cmds->pb;
}

void	init_find_closest_b_spot(t_all *temp)
{
	temp->a.near_rot.r = 0;
	temp->a.near_rot.rrev = 0;
	temp->pred_cmds.pa++;
	temp->pred_cmds.total = count_moves(&temp->pred_cmds);
}
