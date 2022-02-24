/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:01:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:41:21 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	rotate_until_sorted(t_all *all)
{
	int		rotation_direction;

	rotation_direction = 0;
	all->a.forw = (all->a.head)->next;
	all->a.rev = (all->a.head)->prev;
	find_rotation_direction(all, &rotation_direction);
	while (all->a.head->pos != 1)
	{
		if (rotation_direction == RA)
			op_ra(&all->a.head, &all->b.head);
		else if (rotation_direction == RRA)
			op_rra(&all->a.head, &all->b.head);
	}
}

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

void	analyze_fwd(t_all **all)
{
	if (is_smaller_than((*all)->a.forw, ((*all)->a.forw)->next,
			(*all)->a.lims.min, (*all)->a.lims.max))
	{
		(*all)->a.ini_rot.r++;
		(*all)->a.forw = (*all)->a.forw->next;
	}
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
		(*all)->a.forw = (*all)->a.forw->next;
	}
}

void	analyze_bwd(t_all **all)
{
	if (is_bigger_than((*all)->a.rev, (*all)->a.rev->prev,
			(*all)->a.lims.min, (*all)->a.lims.max))
	{
		(*all)->a.ini_rot.rrev++;
		(*all)->a.rev = (*all)->a.rev->prev;
	}
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
		(*all)->a.rev = (*all)->a.rev->prev;
	}
}
