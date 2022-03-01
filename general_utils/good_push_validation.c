/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_push_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:52:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 20:23:19 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

int	is_good_to_place_wo_rot_b(t_elem *b, t_elem *move, t_lims lims_b)
{
	if (!b || !b->next)
		return (1);
	if (is_smaller_than(move, b->prev, lims_b.min, lims_b.max)
		&& is_bigger_than(move, b, lims_b.min, lims_b.max))
		return (1);
	return (0);
}

int	is_good_to_place_wo_rot_a(t_elem *a, t_elem *move, t_lims lims_a)
{
	if (!a || !a->next)
		return (1);
	if (is_smaller_than(move, a, lims_a.min, lims_a.max)
		&& is_bigger_than(move, a->prev,
			lims_a.min, lims_a.max))
		return (1);
	return (0);
}

void	check_if_found_rot_a(t_elem *move, t_stack *stack,
		t_rot *near_rot, t_lims lims)
{
	if (is_bigger_than(stack->forw->prev, move,
			lims.min, lims.max)
		&& is_bigger_than(move, stack->forw,
			lims.min, lims.max))
		near_rot->r++;
	if (is_bigger_than(stack->rev->prev, move,
			lims.min, lims.max)
		&& is_bigger_than(move, stack->rev,
			lims.min, lims.max))
		near_rot->rrev++;
}

void	check_if_found_rot_b(t_elem *cur_b, t_all *temp)
{
	if (is_smaller_than(cur_b, temp->a.forw,
			temp->a.lims.min, temp->a.lims.max)
		&& is_bigger_than(cur_b, temp->a.forw->prev,
			temp->a.lims.min, temp->a.lims.max))
		temp->a.near_rot.r++;
	if (is_smaller_than(temp->a.rev->prev, cur_b,
			temp->a.lims.min, temp->a.lims.max)
		&& is_smaller_than(cur_b, temp->a.rev,
			temp->a.lims.min, temp->a.lims.max))
		temp->a.near_rot.rrev++;
}

int	is_inbetween_bigger(t_elem *fst, t_elem *sec, t_elem *thrd, t_lims lims)
{
	if (is_bigger_than(fst, sec, lims.min, lims.max)
		&& is_bigger_than(sec, thrd, lims.min, lims.max))
		return (1);
	else
		return (0);
}
