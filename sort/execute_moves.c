/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:55 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 17:01:17 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	execute_moves(t_cmds *cmds, t_stack **a,
		t_stack **b, t_limits *lims, int max_len)
{
	if (cmds->type == PUSH_B_FWD)
		execute_pb_forward(cmds, a, b, lims, max_len);
	else if (cmds->type == PUSH_B_BWD)
		execute_pb_backward(cmds, a, b, lims, max_len);
	else if (cmds->type == SWAP_FWD)
		execute_swap_forward(cmds, a, b, max_len);
	else if (cmds->type == SWAP_BWD)
		execute_swap_backward(cmds, a, b, max_len);
}

/* 
	idea create t_stack_lims with min and max for each one of the stacks 
	create structs for everything belonging to a and b instead of the big mess
	if (!is_cmd_table_clean(*cmds))
		printf("Didn't execute all the commands!\n");
*/

void	execute_pb_backward(t_cmds *cmds, t_stack **a,
		t_stack **b, t_limits *lims, int max_len)
{
	while (cmds->rrr-- > 0)
		op_rrr(a, b, max_len);
	while (cmds->rra-- > 0)
		op_rra(a, b, max_len);
	while (cmds->rb-- > 0)
		op_rb(a, b, max_len);
	while (cmds->rrb-- > 0)
		op_rrb(a, b, max_len);
	if (cmds->pb-- > 0)
	{
		set_lims_stack_a_pb(a, b, lims);
		set_lims_stack_b_pb(a, b, lims);
		op_pb(a, b, max_len);
	}
}

void	execute_pb_forward(t_cmds *cmds, t_stack **a,
		t_stack **b, t_limits *lims, int max_len)
{
	while (cmds->rr-- > 0)
		op_rr(a, b, max_len);
	while (cmds->ra-- > 0)
		op_ra(a, b, max_len);
	while (cmds->rb-- > 0)
		op_rb(a, b, max_len);
	while (cmds->rrb-- > 0)
		op_rrb(a, b, max_len);
	if (cmds->pb-- > 0)
	{
		set_lims_stack_a_pb(a, b, lims);
		set_lims_stack_b_pb(a, b, lims);
		op_pb(a, b, max_len);
	}
}

void	execute_swap_forward(t_cmds *cmds, t_stack **a,
		t_stack **b, int max_len)
{
	while (cmds->ra)
	{
		op_ra(a, b, max_len);
		cmds->ra--;
	}
	while (cmds->sa)
	{
		op_sa(a, b, max_len);
		cmds->sa--;
	}
	while (cmds->ss)
	{
		op_ss(a, b, max_len);
		cmds->ss--;
	}
}

void	execute_swap_backward(t_cmds *cmds, t_stack **a,
		t_stack **b, int max_len)
{
	while (cmds->rra)
	{
		op_rra(a, b, max_len);
		cmds->rra--;
	}
	while (cmds->sa)
	{
		op_sa(a, b, max_len);
		cmds->sa--;
	}
	while (cmds->ss)
	{
		op_ss(a, b, max_len);
		cmds->ss--;
	}
}
