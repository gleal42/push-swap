/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:14:27 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 20:49:11 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_lims_stack_a_pb(t_stack **a, t_stack **b, t_limits **lims)
{
	if (!((*a)->next))
		set_both_a_lims_as(&lims, 0);
	else
	{
		if ((*a)->pos == (*lims)->max_a)
			pa_adjust_max_a(*b, *lims);
		if ((*a)->pos == (*lims)->min_a)
			pa_adjust_min_a(*b, *lims);
	}
}

void	set_both_a_lims_as(t_limits ***lims, int value)
{
	(**lims)->min_a = value;
	(**lims)->max_a = value;
}

void	set_lims_stack_b_pb(t_stack **a, t_stack **b, t_limits **lims)
{
	if (!(*b))
		set_both_b_lims_as(&lims, (*a)->pos);
	else
	{
		if ((*a)->pos > (*lims)->max_b)
			(*lims)->max_b = (*a)->pos;
		else if ((*a)->pos < (*lims)->min_b)
			(*lims)->min_b = (*a)->pos;
	}
}

void	set_both_b_lims_as(t_limits ***lims, int value)
{
	(**lims)->min_b = value;
	(**lims)->max_b = value;
}