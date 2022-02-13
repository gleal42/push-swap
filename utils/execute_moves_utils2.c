/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_moves_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:14:37 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 16:45:34 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_lims_stack_b_pa(t_elem **a, t_elem **b, t_all *temp)
{
	if (!((*b)->next))
		set_both_lims_as(&temp->b.lims, 0);
	else
	{
		if ((*b)->pos == temp->b.lims.max)
			pa_adjust_max_b(*a, temp);
		if ((*b)->pos == temp->b.lims.min)
			pa_adjust_min_b(*a, temp);
	}
}

void	set_lims_stack_a_pa(t_elem **a, t_elem **b, t_all *temp)
{
	if (!(*a))
		set_both_lims_as(&temp->a.lims, (*b)->pos);
	else
	{
		if ((*b)->pos > temp->a.lims.max)
			temp->a.lims.max = (*b)->pos;
		else if ((*b)->pos < temp->a.lims.min)
			temp->a.lims.min = (*b)->pos;
	}
}