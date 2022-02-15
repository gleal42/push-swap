/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_limits_max_min.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:54:39 by gleal             #+#    #+#             */
/*   Updated: 2022/02/14 22:08:57 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* We can change the way it analyzes B
** in order to see if we need to go 
** forward of backward instead of just going blindly
** (because B will be organized (i think))
** For the adjust function we can simply
** look at the numbers that were already pushed
*/

void	pa_predict_adjust_max_a(t_elem *b, t_elem *cur_b, t_limits *lims_a, t_limits *lims_b)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims_a->max--;
	if (!cur_b)
		return ;
	if (lims_b->max < lims_a->max)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (cur_b->pos == lims_a->max)
				lims_a->max--;
			else
				repeat = 0;
			check_fwd = cur_b->next;
			check_bckd = cur_b->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims_a->max)
				{
					lims_a->max--;
					repeat++;
				}
				else if (check_bckd->pos == lims_a->max)
				{
					lims_a->max--;
					repeat++;
				}
				if (check_fwd->next)
					check_fwd = check_fwd->next;
				else
					check_fwd = b;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_predict_adjust_min_a(t_elem *b, t_elem *cur_b, t_limits *lims_a, t_limits *lims_b)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims_a->min++;
	if (!cur_b)
		return ;
	if (lims_b->min > lims_a->min)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (cur_b->pos == lims_a->min)
				lims_a->min++;
			else
				repeat = 0;
			check_fwd = cur_b->next;
			check_bckd = cur_b->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims_a->min)
				{
					lims_a->min++;
					repeat++;
				}
				else if (check_bckd->pos == lims_a->min)
				{
					lims_a->min++;
					repeat++;
				}
				if (check_fwd->next)
					check_fwd = check_fwd->next;
				else
					check_fwd = b;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_predict_adjust_max_b(t_elem *a, t_elem *b, t_limits *lims_a, t_limits *lims_b)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	(void)b;
	lims_b->max--;
	if (!a)
		return ;
	if (lims_a->max < lims_b->max)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == lims_b->max)
				lims_b->max--;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims_b->max)
				{
					lims_b->max--;
					repeat++;
				}
				else if (check_bckd->pos == lims_b->max)
				{
					lims_b->max--;
					repeat++;
				}
				if (check_fwd->next)
					check_fwd = check_fwd->next;
				else
					check_fwd = a;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_predict_adjust_min_b(t_elem *a, t_elem *cur_a, t_limits *lims_a, t_limits *lims_b)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims_b->min++;
	if (!cur_a)
		return ;
	if (lims_a->min > lims_b->min)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (cur_a->pos == lims_b->min)
				lims_b->min++;
			else
				repeat = 0;
			check_fwd = cur_a->next;
			check_bckd = cur_a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims_b->min)
				{
					lims_b->min++;
					repeat++;
				}
				else if (check_bckd->pos == lims_b->min)
				{
					lims_b->min++;
					repeat++;
				}
				if (check_fwd->next)
					check_fwd = check_fwd->next;
				else
					check_fwd = a;
				check_bckd = check_bckd->prev;
			}
			repeat = 0;
		}
	}
}
