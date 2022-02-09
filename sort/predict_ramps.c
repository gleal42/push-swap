/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/09 20:11:08 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* We need:
* To have something to update the current b (because when we rotate the head changes)
* To keep track of the numbers we have already pushed (in case we need to go backwards)
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

int	predict_rotationsb_curnbr(t_cmds *temp_cmd, t_stack *a,
		t_stack *b, t_stack *first_nbr, t_stack *cur_stack,
		t_stack **cur_b, t_all *temp, t_limits *limits)
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
			limits->min_b, limits->max_b)
		&& is_prev_nbr_smaller(cur_stack, (*cur_b),
				limits->min_b, limits->max_b))
		return (0);
	if (!(*cur_b)->next)
		temp->forw_b = b;
	else
		temp->forw_b = (*cur_b)->next;
	temp->rev_b = (*cur_b)->prev->prev;
	while (!has_rb && !has_rrb)
	{
		if (!has_rb)
		{
			add_rbs(a, first_nbr, cur_stack, temp->forw_b, &nbr_rot_pred, limits);
			if (is_next_nbr_bigger(cur_stack, temp->forw_b->prev,
					limits->min_b, limits->max_b)
				&& is_prev_nbr_smaller(cur_stack, temp->forw_b,
						limits->min_b, limits->max_b))
				has_rb++;
		}
		if (!has_rrb)
		{
			add_rrbs(a, first_nbr, cur_stack, temp->rev_b, &nbr_rot_pred, limits);
			if (temp->rev_b->next)
			{
				if (is_next_nbr_bigger(cur_stack, temp->rev_b,
						limits->min_b, limits->max_b)
					&& is_prev_nbr_smaller(cur_stack,
							temp->rev_b->next, limits->min_b, limits->max_b))
					has_rrb++;
			}
			else
			{
				if (is_next_nbr_bigger(cur_stack, temp->rev_b,
						limits->min_b, limits->max_b)
					&& is_prev_nbr_smaller(cur_stack, b,
							limits->min_b, limits->max_b))
					has_rrb++;
			}
		}
		if (!has_rb)
		{
			if (temp->forw_b->next)
				temp->forw_b = temp->forw_b->next;
			else
				temp->forw_b = b;
		}
		if (!has_rrb)
			temp->rev_b = (temp->rev_b)->prev;
	}
	update_cur_b(&nbr_rot_pred, cur_b, temp->forw_b, temp->rev_b);
	add_new_rotatesb(b, has_rb, has_rrb, &nbr_rot_pred,
			cur_stack, cur_b, limits);
	temp_cmd->rb += nbr_rot_pred.rb;
	temp_cmd->rrb += nbr_rot_pred.rrb;
	return (0);
}

/* 
* Basically the same as place_in_b but for prediction (check)
 */

void	predict_place_in_b(t_cmds *cmds, t_stack *b,
		t_stack *tobemoved, t_stack **cur_b, t_all *temp)
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
	if (is_next_nbr_bigger(tobemoved, b->prev, temp->lims.min_b,
			temp->lims.max_b) && is_prev_nbr_smaller(tobemoved, b,
				temp->lims.min_b, temp->lims.max_b))
	{
		if (cmds->ra || (!cmds->ra && !cmds->rra))
			has_rb++;
		else if (cmds->rra)
			has_rrb++;
	}
	temp->forw_b = b->next;
	temp->rev_b = b->prev->prev;
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
		if (is_next_nbr_bigger(tobemoved, temp->forw_b->prev,
				temp->lims.min_b, temp->lims.max_b)
			&& is_prev_nbr_smaller(tobemoved, temp->forw_b,
					temp->lims.min_b, temp->lims.max_b))
			has_rb++;
		if (is_next_nbr_bigger(tobemoved, temp->rev_b,
				temp->lims.min_b, temp->lims.max_b)
			&& is_prev_nbr_smaller(tobemoved, temp->rev_b->next,
					temp->lims.min_b, temp->lims.max_b))
			has_rrb++;
		if (!temp->forw_b->next)
			temp->forw_b = b;
		else
			temp->forw_b = (temp->forw_b)->next;
		temp->rev_b = (temp->rev_b)->prev;
	}
	predict_initial_pushmoves(has_rb, has_rrb, cmds);
	update_cur_b(cmds, cur_b, temp->forw_b, temp->rev_b);
	cmds->total = count_moves(cmds);
}

/* 
considerar fazer apenas predict_rotationsb caso tenha mais que 100 algarismos
(porque com 100 está melhor sem isso acho eu)
first prediction pode ser com aquele predictmoves 
*/

/* 2nd while line 20 maybe cur_a->next is not
the best here (for the cases where there is no next) */

int	predict_merge_moves(t_stack *first_nbr, t_stack *firstinramp,
		t_stack *a, t_stack *b, t_cmds *temp_cmd, t_all *temp)
{
	t_stack		*cur_a;
	t_stack		*cur_b;
	t_limits	pred_limits;

	cur_a = first_nbr;
	cur_b = b;
	pred_limits = temp->lims;
	while (cur_a->pos != firstinramp->pos)
	{
		temp_cmd->pb++;
		if (cur_a->pos == first_nbr->pos)
			predict_place_in_b(temp_cmd, b, cur_a, &cur_b, temp);
		else
			predict_rotationsb_curnbr(temp_cmd, a, b,
				first_nbr, cur_a, &cur_b, temp, &pred_limits);
		if (!cur_a->next)
			cur_a = a;
		else
			cur_a = cur_a->next;
	}
	while (!is_next_nbr_bigger(first_nbr->prev, cur_a,
			pred_limits.min_a, pred_limits.max_a))
	{
		temp_cmd->pb++;
		if (cur_a->pos == first_nbr->pos)
			predict_place_in_b(temp_cmd, b, cur_a, &cur_b, temp);
		else
			predict_rotationsb_curnbr(temp_cmd, a, b,
				first_nbr, cur_a, &cur_b, temp, &pred_limits);
		if (!cur_a->next)
			cur_a = a;
		else
			cur_a = cur_a->next;
	}
	temp_cmd->total = count_moves(temp_cmd);
	return (0);
}
