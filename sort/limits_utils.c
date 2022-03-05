/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:06:00 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:07:03 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

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

int	did_find_limit(t_elem *anal, t_lims *lims)
{
	if (anal->pos == lims->max)
	{
		lims->max--;
		return (1);
	}
	if (anal->pos == lims->min)
	{
		lims->min++;
		return (1);
	}
	return (0);
}
