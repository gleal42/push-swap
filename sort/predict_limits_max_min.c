/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_limits_max_min.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:54:39 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 23:46:26 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* We can change the way it analyzes B in order to see if we need to go 
forward of backward instead of just going blindly (because B will be organized (i think))
For the adjust function we can simply
look at the numbers that were already pushed */

void	pa_predict_adjust_max_a(t_elem *b, t_elem *cur_b, t_limits *lims)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims->max_a--;
	if (!cur_b)
		return ;
	if (lims->max_b < lims->max_a)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (cur_b->pos == lims->max_a)
				lims->max_a--;
			else
				repeat = 0;
			check_fwd = cur_b->next;
			check_bckd = cur_b->prev;
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
				if (check_fwd->next)
					check_fwd = check_fwd->next;
				else
					check_fwd = b;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_predict_adjust_min_a(t_elem *b, t_elem *cur_b, t_limits *lims)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims->min_a++;
	if (!cur_b)
		return ;
	if (lims->min_b > lims->min_a)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (cur_b->pos == lims->min_a)
				lims->min_a++;
			else
				repeat = 0;
			check_fwd = cur_b->next;
			check_bckd = cur_b->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims->min_a)
				{
					lims->min_a++;
					repeat++;
				}
				else if (check_bckd->pos == lims->min_a)
				{
					lims->min_a++;
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

void	pa_predict_adjust_max_b(t_elem *a, t_elem *b, t_limits *lims)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	(void)b;
	lims->max_b--;
	if (!a)
		return ;
	if (lims->max_a < lims->max_b)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == lims->max_b)
				lims->max_b--;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims->max_b)
				{
					lims->max_b--;
					repeat++;
				}
				else if (check_bckd->pos == lims->max_b)
				{
					lims->max_b--;
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

void	pa_predict_adjust_min_b(t_elem *a, t_elem *cur_a, t_limits *lims)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims->min_b++;
	if (!cur_a)
		return ;
	if (lims->min_a > lims->min_b)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (cur_a->pos == lims->min_b)
				lims->min_b++;
			else
				repeat = 0;
			check_fwd = cur_a->next;
			check_bckd = cur_a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == lims->min_b)
				{
					lims->min_b++;
					repeat++;
				}
				else if (check_bckd->pos == lims->min_b)
				{
					lims->min_b++;
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
