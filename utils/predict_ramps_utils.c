/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:22:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/15 02:00:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	pred_lims_update(t_elem *first_nbr, t_elem *cur_a, t_elem *cur_b, t_elem *b, t_all *pred)
{
	if (first_nbr->prev->pos == cur_a->pos)
		set_both_lims_as(&pred->a.lims, 0);
	else
	{
		if (cur_a->pos == pred->a.lims.max)
			pred_pb_max_a(b, cur_b, &pred->a.lims, &pred->b.lims);
		if (cur_a->pos == pred->a.lims.min)
			pred_pb_min_a(b, cur_b, &pred->a.lims, &pred->b.lims);
	}
	if (!b)
	{
		if (first_nbr->pos == cur_a->pos)
			set_both_lims_as(&pred->b.lims, cur_a->pos);
	}
	else
	{
		if (cur_a->pos > pred->b.lims.max)
			pred->b.lims.max = cur_a->pos;
		else if (cur_a->pos < pred->b.lims.min)
			pred->b.lims.min = cur_a->pos;
	}
}

/* 
* Basically the same as place_in_b but for prediction (check)
 */

void	pred_ini_rots(t_cmds *cmds, t_elem *b,
		t_elem *tobemoved, t_elem **cur_b, t_all *pred)
{
	int	has_rb;
	int	has_rrb;

	has_rb = 0;
	has_rrb = 0;
	cmds->total = count_moves(cmds);
	if (!b)
		return ;
	if (!b->next)
	{
		has_rb++;
		predict_initial_pushmoves(has_rb, has_rrb, cmds);
		return ;
	}
	if (is_next_nbr_bigger(tobemoved, b->prev, pred->b.lims.min,
			pred->b.lims.max) && is_prev_nbr_smaller(tobemoved, b,
			pred->b.lims.min, pred->b.lims.max))
	{
		if (cmds->ra || (!cmds->ra && !cmds->rra))
			has_rb++;
		else if (cmds->rra)
			has_rrb++;
	}
	pred->b.forw = b->next;
	pred->b.rev = b->prev->prev;
	while (!has_rb && !has_rrb)
	{
		if (cmds->ra > 0)
		{
			cmds->ra--;
			cmds->rr++;
		}
		else
			cmds->rb++;
		if (cmds->rra > 0)
		{
			cmds->rra--;
			cmds->rrr++;
		}
		else
			cmds->rrb++;
		if (is_next_nbr_bigger(tobemoved, pred->b.forw->prev,
				pred->b.lims.min, pred->b.lims.max)
			&& is_prev_nbr_smaller(tobemoved, pred->b.forw,
				pred->b.lims.min, pred->b.lims.max))
			has_rb++;
		if (is_next_nbr_bigger(tobemoved, pred->b.rev,
				pred->b.lims.min, pred->b.lims.max)
			&& is_prev_nbr_smaller(tobemoved, pred->b.rev->next,
				pred->b.lims.min, pred->b.lims.max))
			has_rrb++;
		if (!pred->b.forw->next)
			pred->b.forw = b;
		else
			pred->b.forw = (pred->b.forw)->next;
		pred->b.rev = (pred->b.rev)->prev;
	}
	predict_initial_pushmoves(has_rb, has_rrb, cmds);
	update_cur_b(cmds, cur_b, pred->b.forw, pred->b.rev);
	cmds->total = count_moves(cmds);
}

/* We need:
* To have something to update the
* current b (because when we rotate the head changes)
* To keep track of the numbers we have
* already pushed (in case we need to go backwards)
*/
/* After first return (0);
	if (!b->next)
	{
		if (cur_stack->pos == first_nbr->pos 
			&& temp_cmd 
			&& is_prev_nbr_smaller(cur_stack, cur_b, limits->min_b, limits->max_b))
			nbr_rot_pred.rb++;
		add_new_rotatesb(b, has_rb, has_rrb, &nbr_rot_pred, cur_stack, &cur_b, limits);
		return (0);
} */

int	pred_other_rots(t_cmds *temp_cmd, t_elem *a,
		t_elem *b, t_elem *first_nbr, t_elem *cur_stack,
		t_elem **cur_b, t_all *all, t_lims *lims_b)
{
	t_cmds	nbr_rot_pred;
	int		has_rb;
	int		has_rrb;

	(void)a;
	ft_bzero(&nbr_rot_pred, sizeof(t_cmds));
	has_rb = 0;
	has_rrb = 0;
	if (!b || !b->next)
		return (0);
	if (is_next_nbr_bigger(cur_stack, (*cur_b)->prev,
			lims_b->min, lims_b->max)
		&& is_prev_nbr_smaller(cur_stack, (*cur_b),
			lims_b->min, lims_b->max))
		return (0);
	if (!(*cur_b)->next)
		all->b.forw = b;
	else
		all->b.forw = (*cur_b)->next;
	all->b.rev = (*cur_b)->prev->prev;
	while (!has_rb && !has_rrb)
	{
		if (!has_rb)
		{
			add_rbs(a, first_nbr, cur_stack,
				all->b.forw, &nbr_rot_pred, lims_b);
			if (is_next_nbr_bigger(cur_stack, all->b.forw->prev,
					lims_b->min, lims_b->max)
				&& is_prev_nbr_smaller(cur_stack, all->b.forw,
					lims_b->min, lims_b->max))
				has_rb++;
		}
		if (!has_rrb)
		{
			add_rrbs(a, first_nbr, cur_stack,
				all->b.rev, &nbr_rot_pred, lims_b);
			if (all->b.rev->next)
			{
				if (is_next_nbr_bigger(cur_stack, all->b.rev,
						lims_b->min, lims_b->max)
					&& is_prev_nbr_smaller(cur_stack,
						all->b.rev->next, lims_b->min, lims_b->max))
					has_rrb++;
			}
			else
			{
				if (is_next_nbr_bigger(cur_stack, all->b.rev,
						lims_b->min, lims_b->max)
					&& is_prev_nbr_smaller(cur_stack, b,
						lims_b->min, lims_b->max))
					has_rrb++;
			}
		}
		if (!has_rb)
		{
			if (all->b.forw->next)
				all->b.forw = all->b.forw->next;
			else
				all->b.forw = b;
		}
		if (!has_rrb)
			all->b.rev = (all->b.rev)->prev;
	}
	update_cur_b(&nbr_rot_pred, cur_b, all->b.forw, all->b.rev);
	add_new_rotatesb(has_rb, has_rrb, &nbr_rot_pred);
	temp_cmd->rb += nbr_rot_pred.rb;
	temp_cmd->rrb += nbr_rot_pred.rrb;
	return (0);
}

void	predict_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds)
{
	if ((cmds->rb && cmds->rb <= cmds->rrb) || !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
	}
	else if ((cmds->rrb && cmds->rb > cmds->rrb) || !has_rb)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
	}
}