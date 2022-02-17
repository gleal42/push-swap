/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_limits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 00:40:49 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 00:54:24 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	pred_lims_update(t_elem *first_nbr, t_elem *b, t_all *all, t_all *pred)
{
	if (first_nbr->prev->pos == pred->a.head->pos)
		set_both_lims_as(&pred->a.lims, 0);
	else
		pred_push_orig_lims(all->a.head, &pred->a, &pred->b);
	if (!b)
	{
		if (first_nbr->pos == pred->a.head->pos)
			set_both_lims_as(&pred->b.lims, pred->a.head->pos);
	}
	else
	{
		if (pred->a.head->pos > pred->b.lims.max)
			pred->b.lims.max = pred->a.head->pos;
		else if (pred->a.head->pos < pred->b.lims.min)
			pred->b.lims.min = pred->a.head->pos;
	}
}

/* We can change the way it analyzes B
** in order to see if we need to go 
** forward of backward instead of just going blindly
** (because B will be organized (i think))
** For the adjust function we can simply
** look at the numbers that were already pushed
** checking in b sucks because we are not actually
** pushing, just predicting
** pb 
** ori is a 
** end is b
*/

void	pred_push_orig_lims(t_elem *ori_head, t_stack *cur_ori, t_stack *end)
{
	t_elem	*pushed;
	int		has_lim;

	pushed = cur_ori->head;
	has_lim = 1;
	while (has_lim)
	{
		has_lim = 0;
		pred_lims_check_pushed(&has_lim, ori_head, cur_ori);
		if (end->head
			&& (end->lims.max >= cur_ori->lims.max
				|| end->lims.min <= cur_ori->lims.min))
			pred_lims_check_end(&has_lim, &cur_ori->lims, end);
	}
}

/* check if we should analyze head every time */

void	pred_lims_check_pushed(int *has_lim, t_elem *ori_head, t_stack *cur_ori)
{
	t_elem	*check;
	int		found;

	check = cur_ori->head;
	while (check->pos != ori_head->pos)
	{
		found = 0;
		found = did_find_limit(check, &cur_ori->lims);
		if (found)
		{
			check = cur_ori->head;
			(*has_lim) = 1;
		}
		else
			iterate_stack(&check, ori_head);
	}
}

void	pred_lims_check_end(int *has_lim, t_lims *lims, t_stack *end)
{
	int	found;

	init_stacks_iteration(end, end->head);
	while (end->forw)
	{
		found = 0;
		found += did_find_limit(end->forw, lims);
		found += did_find_limit(end->rev, lims);
		if (found)
		{
			init_stacks_iteration(end, end->head);
			(*has_lim) = 1;
		}
		else
			iterate_fwd_rev(end);
	}
}

int	did_find_limit(t_elem *anal, t_lims *lims)
{
	if (anal->pos == lims->max)
	{
		lims->max--;
		return (1);
	}
	if (anal->pos == lims->min)
	{
		lims->min++;
		return (1);
	}
	return (0);
}
