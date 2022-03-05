/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:19:15 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:15:14 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	execute_merge_ab(t_cmds *cmds, t_stack *a, t_stack *b)
{
	while (cmds->rb-- > 0)
		op_rb(&b->head);
	while (cmds->rrb-- > 0)
		op_rrb(&b->head);
	while (cmds->rr-- > 0)
		op_rr(&a->head, &b->head);
	while (cmds->ra-- > 0)
		op_ra(&a->head);
	while (cmds->rrr-- > 0)
		op_rrr(&a->head, &b->head);
	while (cmds->rra-- > 0)
		op_rra(&a->head);
	if (cmds->pa-- > 0)
	{
		set_lims_ori_push(b, a);
		set_lims_other_push(b, a);
		op_pa(&a->head, &b->head);
	}
}

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
			op_ra(&all->a.head);
		else if (rotation_direction == RRA)
			op_rra(&all->a.head);
	}
}
