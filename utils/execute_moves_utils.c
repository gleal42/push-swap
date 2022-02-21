/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:53:47 by gleal             #+#    #+#             */
/*   Updated: 2022/02/21 23:02:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*		if (end->head
			&& (end->lims.max >= cur_ori->lims.max
				|| end->lims.min <= cur_ori->lims.min))*/

void	set_lims_stack_a_pb(t_elem **a, t_elem **b, t_all *all)
{
	if (!((*a)->next))
		set_both_lims_as(&all->a.lims, 0);
	else
	{
		if ((*b) 
			&&	(all->b.lims.max >= all->a.lims.max
				|| all->b.lims.min <= all->a.lims.min))
			pb_adjust_lims(all);
	}
}

void	set_lims_stack_b_pb(t_elem **a, t_elem **b, t_all *all)
{
	if (!(*b))
		set_both_lims_as(&all->b.lims, (*a)->pos);
	else
	{
		if ((*a)->pos > all->b.lims.max)
			all->b.lims.max = (*a)->pos;
		else if ((*a)->pos < all->b.lims.min)
			all->b.lims.min = (*a)->pos;
	}
}

void	set_both_lims_as(t_lims *lims, int value)
{
	lims->min = value;
	lims->max = value;
}
