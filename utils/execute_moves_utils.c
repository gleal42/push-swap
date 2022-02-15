/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:14:27 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 21:08:25by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_lims_stack_a_pb(t_elem **a, t_elem **b, t_all *all)
{
	if (!((*a)->next))
		set_both_lims_as(&all->a.lims, 0);
	else
	{
		if ((*a)->pos == all->a.lims.max)
			pb_adjust_max_a(*b , &(all->a.lims), &(all->b.lims));
		if ((*a)->pos == all->a.lims.min)
			pb_adjust_min_a(*b, &(all->a.lims), &(all->b.lims));
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

void	set_both_lims_as(t_limits *lims, int value)
{
	lims->min = value;
	lims->max = value;
}