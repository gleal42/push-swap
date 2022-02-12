/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:19:15 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 17:32:21 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	execute_merge_ab(t_cmds *cmds, t_stack **a,
		t_stack **b, t_limits *lims)
{
	while (cmds->rb-- > 0)
		op_rb(a, b);
	while (cmds->rrb-- > 0)
		op_rrb(a, b);
	while (cmds->rr-- > 0)
		op_rr(a, b);
	while (cmds->ra-- > 0)
		op_ra(a, b);
	while (cmds->rrr-- > 0)
		op_rrr(a, b);
	while (cmds->rra-- > 0)
		op_rra(a, b);
	if (cmds->pa-- > 0)
	{
		set_lims_stack_b_pa(a, b, lims);
		set_lims_stack_a_pa(a, b, lims);
		op_pa(a, b);
	}
}
