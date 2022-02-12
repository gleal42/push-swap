/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:55 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 23:41:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	execute_moves(t_cmds *cmds, t_stack *a, t_stack *b, t_all *temp)
{
	if (cmds->type == PUSH_B_FWD)
		execute_pb_forward(cmds, &a->head, &b->head, temp);
	else if (cmds->type == PUSH_B_BWD)
		execute_pb_backward(cmds, &a->head, &b->head, temp);
	else if (cmds->type == SWAP_FWD)
		execute_swap_forward(cmds, &a->head, &b->head);
	else if (cmds->type == SWAP_BWD)
		execute_swap_backward(cmds, &a->head, &b->head);
}

/* 
	idea create t_stack_lims with min and max for each one of the stacks 
	create structs for everything belonging to a and b instead of the big mess
	if (!is_cmd_table_clean(*cmds))
		printf("Didn't execute all the commands!\n");
*/

void	execute_pb_backward(t_cmds *cmds, t_elem **a,
		t_elem **b, t_all *temp)
{
	while (cmds->rrr-- > 0)
		op_rrr(a, b);
	while (cmds->rra-- > 0)
		op_rra(a, b);
	while (cmds->rb-- > 0)
		op_rb(a, b);
	while (cmds->rrb-- > 0)
		op_rrb(a, b);
	if (cmds->pb-- > 0)
	{
		set_lims_stack_a_pb(a, b, temp);
		set_lims_stack_b_pb(a, b, temp);
		op_pb(a, b);
	}
}

void	execute_pb_forward(t_cmds *cmds, t_elem **a,
		t_elem **b, t_all *temp)
{
	while (cmds->rr-- > 0)
		op_rr(a, b);
	while (cmds->ra-- > 0)
		op_ra(a, b);
	while (cmds->rb-- > 0)
		op_rb(a, b);
	while (cmds->rrb-- > 0)
		op_rrb(a, b);
	if (cmds->pb-- > 0)
	{
		set_lims_stack_a_pb(a, b, temp);
		set_lims_stack_b_pb(a, b, temp);
		op_pb(a, b);
	}
}

void	execute_swap_forward(t_cmds *cmds, t_elem **a,
		t_elem **b)
{
	while (cmds->ra)
	{
		op_ra(a, b);
		cmds->ra--;
	}
	while (cmds->sa)
	{
		op_sa(a, b);
		cmds->sa--;
	}
	while (cmds->ss)
	{
		op_ss(a, b);
		cmds->ss--;
	}
}

void	execute_swap_backward(t_cmds *cmds, t_elem **a,
		t_elem **b)
{
	while (cmds->rra)
	{
		op_rra(a, b);
		cmds->rra--;
	}
	while (cmds->sa)
	{
		op_sa(a, b);
		cmds->sa--;
	}
	while (cmds->ss)
	{
		op_ss(a, b);
		cmds->ss--;
	}
}
