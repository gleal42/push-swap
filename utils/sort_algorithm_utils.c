/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:01:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 16:47:46 by gleal            ###   ########.fr       */
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

void	sort_a_b(t_all *all, t_all *temp)
{
	while (temp->a.forw)
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		analyze_fwd(&all, temp);
		analyze_bwd(&all, temp);
		if (have_analyzed_enough(all->exec_cmds, temp->a.ini_rot,
				temp->a.forw, temp->a.rev))
		{
			execute_moves(&all->exec_cmds, &all->a, &all->b, temp);
			init_stacks_iteration(&temp->a, all->a.head);
			ft_bzero(&(temp->a.ini_rot), sizeof(t_rot));
			ft_bzero(&all->exec_cmds, sizeof(t_cmds));
		}
		else if (!temp->a.forw || temp->a.forw->pos == temp->a.rev->pos)
			break ;
	}
}

void	merge_a_b(t_all **all, t_all *temp)
{
	init_stacks_iteration(&temp->a, (*all)->a.head);
	ft_bzero(&(temp->a.ini_rot), sizeof(t_rot));
	while ((*all)->b.head)
	{
		ft_bzero(&temp->exec_cmds, sizeof(t_cmds));
		min_push_b_to_a_moves((*all)->a.head, (*all)->b.head, temp);
		execute_merge_ab(&temp->exec_cmds, &(*all)->a.head,
			&(*all)->b.head, temp);
	}
}
