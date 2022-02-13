/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:13:20 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 16:31:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Consider the numbers that were already pushed in case the next number
* Check if it is considering the right numbers
*/

void	add_rbs(t_elem *a, t_elem *first_nbr,
		t_elem *cur_stack, t_elem *forw_b,
		t_cmds *nbr_rot_pred, t_limits *lims_b)
{
	t_elem	*sent_stack;

	sent_stack = first_nbr;
	while (sent_stack->pos != cur_stack->pos)
	{
		if (is_prev_nbr_smaller(sent_stack, forw_b,
				lims_b->min, lims_b->max)
			&& is_next_nbr_bigger(sent_stack, forw_b->next,
				lims_b->min, lims_b->max))
			nbr_rot_pred->rb++;
		if (!sent_stack->next)
			sent_stack = a;
		else
			sent_stack = sent_stack->next;
	}
}
/* este foi copiado de cima, ver se faz sentido
ou que modificações é preciso fazer.
utilizar os prev era top
 */

void	add_rrbs(t_elem *a, t_elem *first_nbr,
		t_elem *cur_stack, t_elem *rev_b,
		t_cmds *nbr_rot_pred, t_limits *lims_b)
{
	t_elem	*sent_stack;

	sent_stack = first_nbr;
	while (sent_stack->pos != cur_stack->pos)
	{
		if (is_prev_nbr_smaller(sent_stack, rev_b, lims_b->min, lims_b->max)
			&& is_next_nbr_bigger(sent_stack, rev_b->next,
				lims_b->min, lims_b->max))
			nbr_rot_pred->rrb++;
		if (!sent_stack->next)
			sent_stack = a;
		else
			sent_stack = sent_stack->next;
	}
}

/* Have to check if this is actually working
(updating cur_b for every prediction) */

void	update_cur_b(t_cmds *cmds, t_elem **cur_b_head,
		t_elem *fwd_b, t_elem *bwd_b)
{
	int	fwd_total;
	int	rev_total;

	rev_total = 0;
	fwd_total = 0;
	fwd_total = cmds->ra + cmds->rr + cmds->rb;
	rev_total = cmds->rra + cmds->rrr + cmds->rrb;
	if ((fwd_total && fwd_total <= rev_total) || !rev_total)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((rev_total && fwd_total > rev_total) || !fwd_total)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
	if (cmds->rb <= cmds->rrb)
		*cur_b_head = fwd_b;
	else
		*cur_b_head = bwd_b;
}

/* Add compare rbs and rrbs and don't forget to take r and rrs 
into consideration*/

void	add_new_rotatesb(int has_rb,
		int has_rrb, t_cmds *cmds)
{
	if ((cmds->rb <= cmds->rrb && has_rb) || !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
	}
	else if ((cmds->rb > cmds->rrb && has_rrb) || !has_rb)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
	}
}

void	update_predict_limits(t_elem *first_nbr,
		t_elem *cur_a, t_elem *cur_b, t_elem *a,
		t_elem *b, t_all *pred_limits)
{
	(void)a;
	if (first_nbr->prev->pos == cur_a->pos)
	{
		pred_limits->b.lims.max = 0;
		pred_limits->b.lims.min = 0;
	}
	else
	{
		if (cur_a->pos == pred_limits->a.lims.max)
			pa_predict_adjust_max_a(b, cur_b, &pred_limits->a.lims, &pred_limits->b.lims);
		if (cur_a->pos == pred_limits->a.lims.min)
			pa_predict_adjust_min_a(b, cur_b, &pred_limits->a.lims, &pred_limits->b.lims);
	}
	if (!b)
	{
		pred_limits->b.lims.max = cur_a->pos;
		pred_limits->b.lims.min = cur_a->pos;
	}
	else
	{
		if (cur_a->pos > pred_limits->b.lims.max)
			pred_limits->b.lims.max = cur_a->pos;
		else if (cur_a->pos < pred_limits->b.lims.min)
			pred_limits->b.lims.min = cur_a->pos;
	}
}
