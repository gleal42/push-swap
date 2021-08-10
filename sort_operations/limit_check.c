/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:25:03 by gleal             #+#    #+#             */
/*   Updated: 2021/08/10 21:57:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

// We can change the way it analyzes B in order to see if we need to go 
// forward of backward instead of just going blindly (because B will be organized (i think))

void		pa_adjust_max_a(t_stack *b, t_limits *lims)
{
	t_stack *check_fwd;
	t_stack *check_bckd;
	int repeat;

	lims->max_a--;
	if (!b)
		return ;
	if (lims->max_b < lims->max_a)
		return ;
	else
	{
		repeat = 1;
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

void		pa_adjust_min_a(t_stack *b, t_limits *lims)
{
	t_stack *check_fwd;
	t_stack *check_bckd;
	int repeat;

	lims->min_a++;
	if (!b)
		return ;
	if (lims->min_b > lims->min_a)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (b->pos == lims->min_a)
				lims->min_a++;
			else
				repeat = 0;
			check_fwd = b->next;
			check_bckd = b->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims->max_a)
				{
					lims->min_a++;
					repeat++;
				}
				else if (check_bckd->pos == lims->max_a)
				{
					lims->min_a++;
					repeat++;
				}
			}
		}
	}
}