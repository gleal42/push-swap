/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:14:37 by gleal             #+#    #+#             */
/*   Updated: 2022/02/14 23:20:38 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_lims_stack_b_pa(t_elem **a, t_elem **b, t_all *all)
{
	if (!((*b)->next))
		set_both_lims_as(&all->b.lims, 0);
	else
	{
		if ((*b)->pos == all->b.lims.max)
			pa_adjust_max_b(*a, all);
		if ((*b)->pos == all->b.lims.min)
			pa_adjust_min_b(*a, all);
	}
}

void	set_lims_stack_a_pa(t_elem **a, t_elem **b, t_all *all)
{
	if (!(*a))
		set_both_lims_as(&all->a.lims, (*b)->pos);
	else
	{
		if ((*b)->pos > all->a.lims.max)
			all->a.lims.max = (*b)->pos;
		else if ((*b)->pos < all->a.lims.min)
			all->a.lims.min = (*b)->pos;
	}
}