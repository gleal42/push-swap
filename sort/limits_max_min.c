/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits_max_min.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:25:03 by gleal             #+#    #+#             */
/*   Updated: 2022/01/26 16:56:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort.h"

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
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
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
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void		pa_adjust_max_b(t_stack *a, t_limits *lims)
{
	t_stack *check_fwd;
	t_stack *check_bckd;
	int repeat;

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
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void		pa_adjust_min_b(t_stack *a, t_limits *lims)
{
	t_stack *check_fwd;
	t_stack *check_bckd;
	int repeat;

	lims->min_b++;
	if (!a)
		return ;
	if (lims->min_a > lims->min_b)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == lims->min_b)
				lims->min_b++;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
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
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
			repeat = 0;
		}
	}
}