/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:19:15 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:02:56 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	execute_merge_ab(t_cmds *cmds, t_stack *a, t_stack *b)
{
	while (cmds->rb-- > 0)
		op_rb(&a->head, &b->head);
	while (cmds->rrb-- > 0)
		op_rrb(&a->head, &b->head);
	while (cmds->rr-- > 0)
		op_rr(&a->head, &b->head);
	while (cmds->ra-- > 0)
		op_ra(&a->head, &b->head);
	while (cmds->rrr-- > 0)
		op_rrr(&a->head, &b->head);
	while (cmds->rra-- > 0)
		op_rra(&a->head, &b->head);
	if (cmds->pa-- > 0)
	{
		set_lims_ori_push(b, a);
		set_lims_other_push(b, a);
		op_pa(&a->head, &b->head);
	}
}
