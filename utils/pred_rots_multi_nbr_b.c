/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots_multi_nbr_b.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:27:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/25 22:41:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//instead of bigger than target we must check better
//(maybe check if there are other bigger check_fwd)

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_fwd;
	t_elem	*prev_fwd;

	check_fwd = pred->b.forw;
	prev_fwd = check_fwd;
	while (pred->b.forw->pos != pred->a.head->pos
		&& pred->b.forw->pos != (*target)->pos)
	{
		find_next_pred_lower(all, pred, &check_fwd);
		if (check_fwd->pos == prev_fwd->pos)
			update_pred_b_head(all, pred, target, check_fwd);
		else
		{
			pred->b.forw = check_fwd;
			prev_fwd = check_fwd;
			rot_pred->rb++;
		}
	}
}

void	find_next_pred_lower(t_all *all, t_all *pred, t_elem **check_fwd)
{
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	while (sent_stack->pos != pred->a.head->pos)
	{
		if (is_smaller_than(sent_stack, pred->b.forw,
			pred->b.lims.min, pred->b.lims.max)
		&& is_smaller_than(*check_fwd, sent_stack,
			pred->b.lims.min, pred->b.lims.max))
		*check_fwd = sent_stack;
		iterate_stack(&sent_stack, all->a.head);
	}
}

void	update_pred_b_head(t_all *all, t_all *pred, t_elem **target, t_elem	*check_fwd)
{
	if (is_bigger_than(check_fwd, *target,
			pred->b.lims.min, pred->b.lims.max))
	{
		pred->b.forw = *target;
		iterate_stack(target, all->b.head);
	}
	else
		pred->b.forw = pred->a.head;
}

/* este foi copiado de cima, ver se faz sentido
ou que modificações é preciso fazer.
utilizar os prev era top
 */

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_bwd;
	t_elem	*prev_bwd;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	check_bwd = pred->b.rev;
	prev_bwd = check_bwd;
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != (*target)->pos)
	{
		if (is_bigger_than(sent_stack, pred->b.rev,
				pred->b.lims.min, pred->b.lims.max)
			&& is_bigger_than(check_bwd, sent_stack,
				pred->b.lims.min, pred->b.lims.max))
			check_bwd = sent_stack;
		iterate_stack(&sent_stack, all->a.head);
		if (sent_stack->pos == pred->a.head->pos)
		{
			if (check_bwd->pos == prev_bwd->pos)
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
			else
			{
				pred->b.rev = check_bwd;
				prev_bwd = check_bwd;
				rot_pred->rrb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
	}
}