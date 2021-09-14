/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 20:54:29 by gleal             #+#    #+#             */
/*   Updated: 2021/08/07 17:35:44 gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int	is_cmd_table_clean(t_cmds cmds)
{
	if (cmds.sa == 0
		&& cmds.sb == 0
		&& cmds.ss == 0
		&& cmds.ra == 0
		&& cmds.rb == 0
		&& cmds.rr == 0
		&& cmds.pa == 0
		&& cmds.pb == 0
		&& cmds.rra == 0
		&& cmds.rrr == 0
		&& cmds.rrb == 0)
		return (1);
	else
		return (0);
}

void	execute_pb_backward(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len)
{
	while (cmds->rrr > 0)
	{
		op_rrr(a, b, max_len);
		(cmds->rrr)--;
	}
	while (cmds->rra > 0)
	{
		op_rra(a, b, max_len);
		(cmds->rra)--;
	}
	while (cmds->rb > 0)
	{
		op_rb(a, b, max_len);
		(cmds->rb)--;
	}
	while (cmds->rrb > 0)
	{
		op_rrb(a, b, max_len);
		(cmds->rrb)--;
	}
	if (cmds->pb > 0)
	{
		if (!((*a)->next))
		{
			lims->max_b = 0;
			lims->min_b = 0;
		}
		else
		{
			if ((*a)->pos == lims->max_a)
				pa_adjust_max_a(*b, lims);
			if ((*a)->pos == lims->min_a)
				pa_adjust_min_a(*b, lims);
		}
		if (!(*b))
		{
			lims->max_b = (*a)->pos;
			lims->min_b = (*a)->pos;
		}
		else
		{
			if ((*a)->pos > lims->max_b)
				lims->max_b = (*a)->pos;
			else if ((*a)->pos < lims->min_b)
				lims->min_b = (*a)->pos;
		}
		op_pb(a, b, max_len);
		(cmds->pb)--;
	}
	if (!is_cmd_table_clean(*cmds))
		printf("Didn't execute all the commands!\n");
}

void	execute_pb_forward(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len)
{
	while (cmds->rr > 0)
	{
		op_rr(a, b, max_len);
		(cmds->rr)--;
	}
	while (cmds->ra > 0)
	{
		op_ra(a, b, max_len);
		(cmds->ra)--;
	}
	while (cmds->rb > 0)
	{
		op_rb(a, b, max_len);
		(cmds->rb)--;
	}
	while (cmds->rrb > 0)
	{
		op_rrb(a, b, max_len);
		(cmds->rrb)--;
	}
	if (cmds->pb > 0)
	{
		if (!((*a)->next))
		{
			lims->max_b = 0;
			lims->min_b = 0;
		}
		else
		{
			if ((*a)->pos == lims->max_a)
				pa_adjust_max_a(*b, lims);
			if ((*a)->pos == lims->min_a)
				pa_adjust_min_a(*b, lims);
		}
		if (!(*b))
		{
			lims->max_b = (*a)->pos;
			lims->min_b = (*a)->pos;
		}
		else
		{
			if ((*a)->pos > lims->max_b)
				lims->max_b = (*a)->pos;
			else if ((*a)->pos < lims->min_b)
				lims->min_b = (*a)->pos;
		}
		op_pb(a, b, max_len);
		(cmds->pb)--;
	}
	if (!is_cmd_table_clean(*cmds))
		printf("Didn't execute all the commands!\n");
}

void	execute_swap_forward(t_cmds *cmds, t_stack **a, t_stack **b, int max_len)
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
	if (!is_cmd_table_clean(*cmds))
		printf("Didn't execute all the commands!\n");
}

void	execute_swap_backward(t_cmds *cmds, t_stack **a, t_stack **b, int max_len)
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
	if (!is_cmd_table_clean(*cmds))
		printf("Didn't execute all the commands!\n");
}

void	execute_moves(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len)
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

void	execute_merge_ab(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len)
{
	while (cmds->rr > 0)
	{
		op_rr(a, b, max_len);
		(cmds->rr)--;
	}
	while (cmds->ra > 0)
	{
		op_ra(a, b, max_len);
		(cmds->ra)--;
	}
	while (cmds->rrr > 0)
	{
		op_rrr(a, b, max_len);
		(cmds->rrr)--;
	}
	while (cmds->rra > 0)
	{
		op_rra(a, b, max_len);
		(cmds->rra)--;
	}
	if (cmds->pb > 0)
	{
		if (!((*b)->next))
		{
			lims->max_b = 0;
			lims->min_b = 0;
		}
		else
		{
			if ((*b)->pos == lims->max_b)
				pb_adjust_max_b(*a, lims);
			if ((*b)->pos == lims->min_b)
				pb_adjust_min_b(*a, lims);
		}
		if (!(*a))
		{
			lims->max_a = (*b)->pos;
			lims->min_a = (*b)->pos;
		}
		else
		{
			if ((*b)->pos > lims->max_a)
				lims->max_a = (*b)->pos;
			else if ((*b)->pos < lims->min_a)
				lims->min_a = (*b)->pos;
		}
		op_pa(a, b, max_len);
		(cmds->pb)--;
	}
}
