/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:01:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/10 17:58:04 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	rotate_until_sorted(t_all *all, int max_len)
{
	int		rotation_direction;

	rotation_direction = 0;
	all->forw_a = (all->a)->next;
	all->rev_a = (all->a)->prev;
	find_rotation_direction(all, &rotation_direction);
	while (all->a->pos != 1)
	{
		if (rotation_direction == RA)
			op_ra(&all->a, &all->b, max_len);
		else if (rotation_direction == RRA)
			op_rra(&all->a, &all->b, max_len);
	}
}

void	sort_a_b(t_all *all, t_all *temp, int max_a)
{
	while (temp->forw_a)
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		analyze_fwd(&all, temp);
		analyze_bwd(&all, temp);
		if (have_analyzed_enough(all->exec_cmds, temp->ini_rot_a,
				temp->forw_a, temp->rev_a))
		{
			execute_moves(&all->exec_cmds, &all->a, &all->b, &temp->lims, max_a);
			init_stacks_iteration_a(temp, all);
			ft_bzero(&(temp->ini_rot_a), sizeof(t_rot_a));
			ft_bzero(&all->exec_cmds, sizeof(t_cmds));
		}
		else if (!temp->forw_a || temp->forw_a->pos == temp->rev_a->pos)
			break ;
	}
}

void	merge_a_b(t_all **all, t_all *temp, int max_a)
{
	init_stacks_iteration_a(temp, *all);
	ft_bzero(&(temp->ini_rot_a), sizeof(t_rot_a));
	while ((*all)->b)
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		min_push_b_to_a_moves((*all)->a, (*all)->b, temp);
		execute_merge_ab(&temp->exec_cmds, &(*all)->a, &(*all)->b, &temp->lims, max_a);
	}
}