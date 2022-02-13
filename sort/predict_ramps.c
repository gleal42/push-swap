/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 16:58:14 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

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

int	predict_rotationsb_curnbr(t_cmds *temp_cmd, t_elem *a,
		t_elem *b, t_elem *first_nbr, t_elem *cur_stack,
		t_elem **cur_b, t_all *temp, t_limits *lims_b)
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
		temp->b.forw = b;
	else
		temp->b.forw = (*cur_b)->next;
	temp->b.rev = (*cur_b)->prev->prev;
	while (!has_rb && !has_rrb)
	{
		if (!has_rb)
		{
			add_rbs(a, first_nbr, cur_stack,
				temp->b.forw, &nbr_rot_pred, lims_b);
			if (is_next_nbr_bigger(cur_stack, temp->b.forw->prev,
					lims_b->min, lims_b->max)
				&& is_prev_nbr_smaller(cur_stack, temp->b.forw,
					lims_b->min, lims_b->max))
				has_rb++;
		}
		if (!has_rrb)
		{
			add_rrbs(a, first_nbr, cur_stack,
				temp->b.rev, &nbr_rot_pred, lims_b);
			if (temp->b.rev->next)
			{
				if (is_next_nbr_bigger(cur_stack, temp->b.rev,
						lims_b->min, lims_b->max)
					&& is_prev_nbr_smaller(cur_stack,
						temp->b.rev->next, lims_b->min, lims_b->max))
					has_rrb++;
			}
			else
			{
				if (is_next_nbr_bigger(cur_stack, temp->b.rev,
						lims_b->min, lims_b->max)
					&& is_prev_nbr_smaller(cur_stack, b,
						lims_b->min, lims_b->max))
					has_rrb++;
			}
		}
		if (!has_rb)
		{
			if (temp->b.forw->next)
				temp->b.forw = temp->b.forw->next;
			else
				temp->b.forw = b;
		}
		if (!has_rrb)
			temp->b.rev = (temp->b.rev)->prev;
	}
	update_cur_b(&nbr_rot_pred, cur_b, temp->b.forw, temp->b.rev);
	add_new_rotatesb(has_rb, has_rrb, &nbr_rot_pred);
	temp_cmd->rb += nbr_rot_pred.rb;
	temp_cmd->rrb += nbr_rot_pred.rrb;
	return (0);
}

/* 
* Basically the same as place_in_b but for prediction (check)
 */

void	predict_place_in_b(t_cmds *cmds, t_elem *b,
		t_elem *tobemoved, t_elem **cur_b, t_all *temp)
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
	if (is_next_nbr_bigger(tobemoved, b->prev, temp->b.lims.min,
			temp->b.lims.max) && is_prev_nbr_smaller(tobemoved, b,
			temp->b.lims.min, temp->b.lims.max))
	{
		if (cmds->ra || (!cmds->ra && !cmds->rra))
			has_rb++;
		else if (cmds->rra)
			has_rrb++;
	}
	temp->b.forw = b->next;
	temp->b.rev = b->prev->prev;
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
		if (is_next_nbr_bigger(tobemoved, temp->b.forw->prev,
				temp->b.lims.min, temp->b.lims.max)
			&& is_prev_nbr_smaller(tobemoved, temp->b.forw,
				temp->b.lims.min, temp->b.lims.max))
			has_rb++;
		if (is_next_nbr_bigger(tobemoved, temp->b.rev,
				temp->b.lims.min, temp->b.lims.max)
			&& is_prev_nbr_smaller(tobemoved, temp->b.rev->next,
				temp->b.lims.min, temp->b.lims.max))
			has_rrb++;
		if (!temp->b.forw->next)
			temp->b.forw = b;
		else
			temp->b.forw = (temp->b.forw)->next;
		temp->b.rev = (temp->b.rev)->prev;
	}
	predict_initial_pushmoves(has_rb, has_rrb, cmds);
	update_cur_b(cmds, cur_b, temp->b.forw, temp->b.rev);
	cmds->total = count_moves(cmds);
}

/* 
considerar fazer apenas predict_rotationsb caso tenha mais que 100 algarismos
(porque com 100 está melhor sem isso acho eu)
first prediction pode ser com aquele predictmoves 
*/

/* 2nd while line 20 maybe cur_a->next is not
the best here (for the cases where there is no next) */

int	predict_merge_moves(t_all *all, t_all *temp, t_elem *firstinramp)
{
	t_elem		*cur_a;
	t_elem		*cur_b;
	t_limits	pred_lim_a;
	t_limits	pred_lim_b;

	cur_a = all->a.ramp.first_nbr;
	cur_b = all->b.head;
	pred_lim_a = temp->a.lims;
	pred_lim_b = temp->b.lims;
	while (cur_a->pos != firstinramp->pos)
	{
		(&all->a.ramp.init_cmds)->pb++;
		if (cur_a->pos == all->a.ramp.first_nbr->pos)
			predict_place_in_b(&all->a.ramp.init_cmds,
				all->b.head, cur_a, &cur_b, temp);
		else
			predict_rotationsb_curnbr(&all->a.ramp.init_cmds, all->a.head, all->b.head,
				all->a.ramp.first_nbr, cur_a, &cur_b, temp, &pred_lim_b);
		if (!cur_a->next)
			cur_a = all->a.head;
		else
			cur_a = cur_a->next;
	}
	while (!is_next_nbr_bigger(all->a.ramp.first_nbr->prev, cur_a,
			pred_lim_a.min, pred_lim_a.max))
	{
		(&all->a.ramp.init_cmds)->pb++;
		if (cur_a->pos == all->a.ramp.first_nbr->pos)
			predict_place_in_b(&all->a.ramp.init_cmds,
				all->b.head, cur_a, &cur_b, temp);
		else
			predict_rotationsb_curnbr(&all->a.ramp.init_cmds, all->a.head, all->b.head,
				all->a.ramp.first_nbr, cur_a, &cur_b, temp, &pred_lim_b);
		if (!cur_a->next)
			cur_a = all->a.head;
		else
			cur_a = cur_a->next;
	}
	(&all->a.ramp.init_cmds)->total = count_moves(&all->a.ramp.init_cmds);
	return (0);
}
