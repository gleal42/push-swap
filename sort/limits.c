/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:48:22 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:06:56 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	set_lims_ori_push(t_stack *ori, t_stack *other)
{
	if (!(ori->head->next))
		set_both_lims_as(&ori->lims, 0);
	else
	{
		if ((other->head)
			&& (other->lims.max >= ori->lims.max
				|| other->lims.min <= ori->lims.min))
			adj_lims_ori_push(ori, other);
	}
}

void	set_lims_other_push(t_stack *ori, t_stack *other)
{
	if (!(other->head))
		set_both_lims_as(&other->lims, ori->head->pos);
	else
	{
		if (ori->head->pos > other->lims.max)
			other->lims.max = ori->head->pos;
		else if (ori->head->pos < other->lims.min)
			other->lims.min = ori->head->pos;
	}
}

void	pred_lims_check_end(int *has_lim, t_lims *lims, t_stack *end)
{
	int	found;

	init_stacks_iteration(end, end->head);
	while (end->forw)
	{
		found = 0;
		found += did_find_limit(end->forw, lims);
		found += did_find_limit(end->rev, lims);
		if (found)
		{
			init_stacks_iteration(end, end->head);
			(*has_lim) = 1;
		}
		else
			iterate_fwd_rev_toend(end);
	}
}
