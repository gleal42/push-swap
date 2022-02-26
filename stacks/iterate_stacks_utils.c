/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_stacks_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:49:26 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 21:49:28 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	init_stacks_iteration(t_stack *tobeinit, t_elem *ref)
{
	tobeinit->forw = ref;
	tobeinit->rev = ref;
}

void	iterate_fwd_rev_toend(t_stack *to_iter)
{
	to_iter->forw = to_iter->forw->next;
	to_iter->rev = to_iter->rev->prev;
}

void	iterate_fwd_rev_noend(t_stack *to_iter, t_elem *stack_head)
{
	iterate_stack(&to_iter->forw, stack_head);
	to_iter->rev = to_iter->rev->prev;
}

void	iterate_stack(t_elem **to_iter, t_elem *stack_head)
{
	if ((*to_iter)->next)
		*to_iter = (*to_iter)->next;
	else
		*to_iter = stack_head;
}
