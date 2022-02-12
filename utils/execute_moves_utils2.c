/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:14:37 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 17:18:49 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_lims_stack_b_pa(t_stack **a, t_stack **b, t_limits *lims)
{
	if (!((*b)->next))
		set_both_b_lims_as(lims, 0);
	else
	{
		if ((*b)->pos == lims->max_b)
			pa_adjust_max_b(*a, lims);
		if ((*b)->pos == lims->min_b)
			pa_adjust_min_b(*a, lims);
	}
}

void	set_lims_stack_a_pa(t_stack **a, t_stack **b, t_limits *lims)
{
	if (!(*a))
		set_both_a_lims_as(lims, (*b)->pos);
	else
	{
		if ((*b)->pos > lims->max_a)
			lims->max_a = (*b)->pos;
		else if ((*b)->pos < lims->min_a)
			lims->min_a = (*b)->pos;
	}
}