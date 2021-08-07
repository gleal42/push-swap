/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:25:03 by gleal             #+#    #+#             */
/*   Updated: 2021/08/07 18:41:12 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

void		adjust_max_a(t_stack *b, t_limits *lims)
{
	t_stack *check_fwd;
	t_stack *check_bckd;
	int repeat;

	repeat = 1;
	if (!b)
		return ;
	if (lims->max_b < lims->max_a)
		return ;
	else
	{
		while (repeat)
		{
			if (b->pos == lims->max_a)
				lims->max_a--;
			else
				repeat = 0;
			check_fwd = b->next;
			check_bckd = b->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims->max_a)
				{
					lims->max_a--;
					repeat++;
				}
				else if (check_bckd->pos == lims->max_a)
				{
					lims->max_a--;
					repeat++;
				}
			}
		}
	}
}