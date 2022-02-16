/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_limits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:54:39 by gleal             #+#    #+#             */
/*   Updated: 2022/02/16 01:39:57by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	pred_lims_update(t_elem *first_nbr, t_elem *b, t_all *pred)
{
	if (first_nbr->prev->pos == pred->a.head->pos)
		set_both_lims_as(&pred->a.lims, 0);
	else
	{
			pred_push_orig_max(b, &pred->a, &pred->b);
		if (pred->a.head->pos == pred->a.lims.min)
			pred_push_orig_min(b, &pred->a, &pred->b);
	}
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

void	pred_push_orig_max(t_elem *ori_head, t_stack *cur_ori, t_stack *end)
{
	t_elem	*pushed;
	int		found_lim;

	pushed = cur_ori->head;
	if (cur_ori->head->pos == cur_ori->lims.max)
	{
		cur_ori->lims.max--;
		found_lim = 1;
	}
	while (found_lim)
	{
		found_lim = 0;
		pred_lims_check_pushed();
		if (end->head
		&& (end->lims.max >= cur_ori->lims.max
			|| end->lims.min  <= cur_ori->lims.min))
			pred_lims_check_b();
	}
}

/* check if we should analyze head every time */

void	pred_lims_check_b()
{
	if (end->head->pos == cur_ori->lims.max)
		cur_ori->lims.max--;
	end->forw = end->head->next;
	end->rev = end->head->prev;
	while (end->forw)
	{
		(*found_lim) = did_find_limit(end->head);
		(*found_lim) = did_find_limit(end->forw);
		(*found_lim) = did_find_limit(end->rev);
		if (end->forw->next)
			end->forw = end->forw->next;
		else
			end->forw = ori_head;
		end->rev = end->rev->prev;
	}
}

int		did_find_limit(t_elem *anal)
{
	if (anal->pos == cur_ori->lims.max)
	{
		cur_ori->lims.max--;
		return (1);
	}
	if (anal->pos == cur_ori->lims.min)
	{
		cur_ori->lims.min++;
		return (1);
	}
}

/* void	pred_push_orig_min(t_elem *ori_head, t_stack *ori, t_stack *end)
{
	int		repeat;

	ori->lims.min++;
	if (!end->head)
		return ;
	if (end->lims.min > ori->lims.min)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (end->head->pos == ori->lims.min)
				ori->lims.min++;
			else
				repeat = 0;
			end->forw = end->head->next;
			end->rev = end->head->prev;
			while (end->forw)
			{
				if (end->forw->pos == ori->lims.min)
				{
					ori->lims.min++;
					repeat++;
				}
				else if (end->rev->pos == ori->lims.min)
				{
					ori->lims.min++;
					repeat++;
				}
				if (end->forw->next)
					end->forw = end->forw->next;
				else
					end->forw = ori_head;
				end->rev = end->rev->prev;
			}
		}
	}
}
 */

/* void	pred_push_orig_max(t_elem *ori_head, t_stack *cur_ori, t_stack *end)
{
	int		repeat;

	cur_ori->lims.max--;
	if (!end->head || end->lims.max < cur_ori->lims.max)
		return ;
	else
	{
		repeat = 1;
		while (repeat)
		{
			if (end->head->pos == cur_ori->lims.max)
				cur_ori->lims.max--;
			else
				repeat = 0;
			end->forw = end->head->next;
			end->rev = end->head->prev;
			while (end->forw)
			{
				if (end->forw->pos == cur_ori->lims.max)
				{
					cur_ori->lims.max--;
					repeat++;
				}
				else if (end->rev->pos == cur_ori->lims.max)
				{
					cur_ori->lims.max--;
					repeat++;
				}
				if (end->forw->next)
					end->forw = end->forw->next;
				else
					end->forw = ori_head;
				end->rev = end->rev->prev;
			}
		}
	}
