/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:22:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 19:06:58 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* 
* Same as place_in_b but updating
 */

/* void	pred_ini_rots(t_cmds *cmds, t_elem *b,
		t_elem *tobemoved, t_elem **cur_b, t_all *pred)
{
	int	closer_fwd;
	int	closer_bwd;

	closer_fwd = 0;
	closer_bwd = 0;
	cmds->total = count_moves(cmds);
	if (is_good_to_place_wo_rot_b(b, tobemoved, pred->b.lims))
		return ;
	init_stacks_iteration(&pred->b, b);	
	while (!closer_fwd && !closer_bwd)
	{
		add_double_rots_a(cmds);
		check_if_found_rot(pred, tobemoved, &closer_fwd, &closer_bwd);
		iterate_stack(pred->b.forw, b);
		pred->b.rev = (pred->b.rev)->prev;
	}
	predict_initial_pushmoves(closer_fwd, closer_bwd, cmds);
	update_cur_b(cmds, cur_b, pred->b.forw, pred->b.rev);
	cmds->total = count_moves(cmds);
} */

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