/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:48:22 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:06:43 by gleal            ###   ########.fr       */
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

void	set_both_lims_as(t_lims *lims, int value)
{
	lims->min = value;
	lims->max = value;
}

void	adj_lims_ori_push(t_stack *origin, t_stack *other)
{
	int		has_lim;
	t_stack	temp;

	temp = *other;
	has_lim = 1;
	while (has_lim)
	{
		has_lim = 0;
		if (temp.head
			&& (temp.lims.max >= origin->lims.max
				|| temp.lims.min <= origin->lims.min))
			pred_lims_check_end(&has_lim, &origin->lims, &temp);
	}
}
