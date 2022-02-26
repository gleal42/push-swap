/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:25:04 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 21:00:02 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	pred_ramp_rots(t_all *pred, t_all *all,
		t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (valid(pred->a.head, ref, &pred->a.lims))
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(all->a.ramp.first_nbr, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		{
			place_in_b(all->b.head, pred, pred->a.head, &all->a.ramp.init_cmds);
			if (all->a.ramp.init_cmds.rb || all->a.ramp.init_cmds.rr)
				pred->b.head = pred->b.forw;
			else if (all->a.ramp.init_cmds.rrb || all->a.ramp.init_cmds.rrr)
				pred->b.head = pred->b.rev;
		}
		else
			pred_other_rots(pred, all, &all->a.ramp.init_cmds);
		iterate_stack(&pred->a.head, all->a.head);
	}
}

void	update_pred_lims_b(t_all *all, t_lims *lims_b, t_elem *check)
{
	int		min;
	int		max;
	t_elem	*temp;

	temp = all->b.head;
	min = 0;
	max = 0;
	while (temp)
	{
		update_max_min(temp, &min, &max);
		temp = temp->next;
	}
	temp = all->a.ramp.first_nbr;
	while (temp && temp->pos != check->pos)
	{
		update_max_min(temp, &min, &max);
		temp = temp->next;
	}
	lims_b->max = max;
	lims_b->min = min;
}

void	update_max_min(t_elem	*temp, int *min, int *max)
{
	if (!(*min) || temp->pos < (*min))
		(*min) = temp->pos;
	if (!(*max) || temp->pos > (*max))
		(*max) = temp->pos;
}
