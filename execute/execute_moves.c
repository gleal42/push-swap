/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:55 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:14:02 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	execute_moves(t_cmds *cmds, t_stack *a, t_stack *b)
{
	if (cmds->type == PUSH_B_FWD)
		execute_pb_forward(cmds, a, b);
	else if (cmds->type == PUSH_B_BWD)
		execute_pb_backward(cmds, a, b);
	else if (cmds->type == SWAP_FWD)
		execute_swap_forward(cmds, &a->head, &b->head);
	else if (cmds->type == SWAP_BWD)
		execute_swap_backward(cmds, &a->head, &b->head);
}

void	execute_pb_backward(t_cmds *cmds, t_stack *a, t_stack *b)
{
	while (cmds->rrr-- > 0)
		op_rrr(&a->head, &b->head);
	while (cmds->rra-- > 0)
		op_rra(&a->head);
	while (cmds->rb-- > 0)
		op_rb(&b->head);
	while (cmds->rrb-- > 0)
		op_rrb(&b->head);
	if (cmds->pb-- > 0)
	{
		set_lims_ori_push(a, b);
		set_lims_other_push(a, b);
		op_pb(&a->head, &b->head);
	}
}

void	execute_pb_forward(t_cmds *cmds, t_stack *a, t_stack *b)
{
	while (cmds->rr-- > 0)
		op_rr(&a->head, &b->head);
	while (cmds->ra-- > 0)
		op_ra(&a->head);
	while (cmds->rb-- > 0)
		op_rb(&b->head);
	while (cmds->rrb-- > 0)
		op_rrb(&b->head);
	if (cmds->pb-- > 0)
	{
		set_lims_ori_push(a, b);
		set_lims_other_push(a, b);
		op_pb(&a->head, &b->head);
	}
}

void	execute_swap_forward(t_cmds *cmds, t_elem **a, t_elem **b)
{
	while (cmds->ra)
	{
		op_ra(a);
		cmds->ra--;
	}
	while (cmds->sa)
	{
		op_sa(a);
		cmds->sa--;
	}
	while (cmds->ss)
	{
		op_ss(a, b);
		cmds->ss--;
	}
}

void	execute_swap_backward(t_cmds *cmds, t_elem **a, t_elem **b)
{
	while (cmds->rra)
	{
		op_rra(a);
		cmds->rra--;
	}
	while (cmds->sa)
	{
		op_sa(a);
		cmds->sa--;
	}
	while (cmds->ss)
	{
		op_ss(a, b);
		cmds->ss--;
	}
}
