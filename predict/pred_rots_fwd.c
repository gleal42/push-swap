/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_fwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:27:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/27 19:08:31y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"

//instead of bigger than target we must check better
//(maybe check if there are other bigger check_fwd)

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_fwd;
	t_elem	*prev_fwd;

	prev_fwd = NULL;
	check_fwd = pred->b.forw;
	while (pred->b.forw->pos != pred->a.head->pos
		&& pred->b.forw->pos != (*target)->pos)
	{
		add_rbs_find_next_lower(all, pred, &check_fwd, &prev_fwd);
		if (check_fwd->pos == pred->b.forw->pos)
			update_pred_b_head_fwd(pred, target, check_fwd);
		else
		{
			pred->b.forw = check_fwd;
			rot_pred->rb++;
		}
	}
	if (pred->b.forw->pos == (*target)->pos)
		iterate_stack(target, all->b.head);
}

void	add_rbs_find_next_lower(t_all *all, t_all *pred, t_elem **check_fwd, t_elem **prev_fwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while ((*check_fwd)->pos != pred->a.head->pos &&
		sent_stack->pos != pred->a.head->pos)
	{
		if ((is_bigger_than(pred->b.forw, sent_stack, pred->b.lims.min, pred->b.lims.max) || (pred->b.forw->pos == sent_stack->pos))
			&& ((prev_fwd == NULL || is_smaller_than(sent_stack, *check_fwd, pred->b.lims.min, pred->b.lims.max))))
		{
			*check_fwd = sent_stack;
			*prev_fwd = *check_fwd;
			sent_stack = all->a.ramp.first_nbr;
		}
		else
			iterate_stack(&sent_stack, all->a.head);
	}
}

/*if (is_smaller_than(check_fwd, *target,
		pred->b.lims.min, pred->b.lims.max))*/

void	update_pred_b_head_fwd(t_all *pred, t_elem **target, t_elem	*check_fwd)
{
	if ((is_bigger_than((*target)->prev, pred->a.head, pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(pred->a.head, check_fwd, pred->b.lims.min, pred->b.lims.max))
		|| (is_bigger_than(check_fwd, pred->a.head, pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(pred->a.head, *target, pred->b.lims.min, pred->b.lims.max)))
			pred->b.forw = pred->a.head;
	else
		pred->b.forw = *target;
}
