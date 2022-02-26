/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_bwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:11:43 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 21:00:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_bwd;
	t_elem	*prev_bwd;

	check_bwd = pred->b.rev;
	prev_bwd = check_bwd;
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != (*target)->pos)
	{
		find_next_pred_bigger(all, pred, &check_bwd);
		if (check_bwd->pos == prev_bwd->pos)
			update_pred_b_head_bwd(pred, target, check_bwd);
		else
		{
			pred->b.rev = check_bwd;
			prev_bwd = check_bwd;
			rot_pred->rrb++;
		}
	}
}

void	find_next_pred_bigger(t_all *all, t_all *pred, t_elem **check_bwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if (is_bigger_than(sent_stack, pred->b.rev,
				pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(*check_bwd, sent_stack,
				pred->b.lims.min, pred->b.lims.max))
			*check_bwd = sent_stack;
		iterate_stack(&sent_stack, all->a.head);
	}
}

void	update_pred_b_head_bwd(t_all *pred, t_elem **target, t_elem	*check_bwd)
{
	if (is_smaller_than(check_bwd, *target,
			pred->b.lims.min, pred->b.lims.max))
	{
		pred->b.rev = *target;
		(*target) = (*target)->prev;
	}
	else
		pred->b.rev = pred->a.head;
}
