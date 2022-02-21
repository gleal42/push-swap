/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:04:05 by gleal             #+#    #+#             */
/*   Updated: 2022/02/21 23:04:26 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	pb_adjust_lims(t_all *all)
{
	int		has_lim;
	t_stack	temp;

	temp = all->b;
	has_lim = 1;
	while (has_lim)
	{
		has_lim = 0;
		if (temp.head
			&& (temp.lims.max >= all->a.lims.max
				|| temp.lims.min <= all->a.lims.min))
			pred_lims_check_end(&has_lim, &all->a.lims, &temp);
	}
}

void	pa_adjust_max_b(t_elem *a, t_all *all)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	all->b.lims.max--;
	if (!a)
		return ;
	if (all->a.lims.max < all->b.lims.max)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == all->b.lims.max)
				all->b.lims.max--;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == all->b.lims.max)
				{
					all->b.lims.max--;
					repeat++;
				}
				else if (check_bckd->pos == all->b.lims.max)
				{
					all->b.lims.max--;
					repeat++;
				}
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_adjust_min_b(t_elem *a, t_all *all)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	all->b.lims.min++;
	if (!a)
		return ;
	if (all->a.lims.min > all->b.lims.min)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == all->b.lims.min)
				all->b.lims.min++;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == all->b.lims.min)
				{
					all->b.lims.min++;
					repeat++;
				}
				else if (check_bckd->pos == all->b.lims.min)
				{
					all->b.lims.min++;
					repeat++;
				}
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
			repeat = 0;
		}
	}
}
