/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits_max_min.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:25:03 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 23:20:21 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	pb_adjust_max_a(t_elem *b, t_limits *lims_a, t_limits *lims_b)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims_a->max--;
	if (!b)
		return ;
	if (lims_b->max < lims_a->max)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (b->pos == lims_a->max)
				lims_a->max--;
			else
				repeat = 0;
			check_fwd = b->next;
			check_bckd = b->prev;
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
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pb_adjust_min_a(t_elem *b, t_limits *lims_a, t_limits *lims_b)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	lims_a->min++;
	if (!b)
		return ;
	if (lims_b->min > lims_a->min)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (b->pos == lims_a->min)
				lims_a->min++;
			else
				repeat = 0;
			check_fwd = b->next;
			check_bckd = b->prev;
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
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_adjust_max_b(t_elem *a, t_all *temp)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	temp->b.lims.max--;
	if (!a)
		return ;
	if (temp->a.lims.max < temp->b.lims.max)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == temp->b.lims.max)
				temp->b.lims.max--;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == temp->b.lims.max)
				{
					temp->b.lims.max--;
					repeat++;
				}
				else if (check_bckd->pos == temp->b.lims.max)
				{
					temp->b.lims.max--;
					repeat++;
				}
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
		}
	}
}

void	pa_adjust_min_b(t_elem *a, t_all *temp)
{
	t_elem	*check_fwd;
	t_elem	*check_bckd;
	int		repeat;

	temp->b.lims.min++;
	if (!a)
		return ;
	if (temp->a.lims.min > temp->b.lims.min)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (a->pos == temp->b.lims.min)
				temp->b.lims.min++;
			else
				repeat = 0;
			check_fwd = a->next;
			check_bckd = a->prev;
			while (check_fwd)
			{
				if (check_fwd->pos == temp->b.lims.min)
				{
					temp->b.lims.min++;
					repeat++;
				}
				else if (check_bckd->pos == temp->b.lims.min)
				{
					temp->b.lims.min++;
					repeat++;
				}
				check_fwd = check_fwd->next;
				check_bckd = check_bckd->prev;
			}
			repeat = 0;
		}
	}
}
