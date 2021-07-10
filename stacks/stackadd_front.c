/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackadd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:38:23 by gleal             #+#    #+#             */
/*   Updated: 2021/07/10 17:18:12 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stacktadd_front(t_stack **stack, t_stack *new_stack)
{
	t_stack *last;

	last = stack_last(*stack);
	new_stack->prev = last;
	if (!stack || !new_stack)
		return ;
	if (*stack)
		new_stack->next = *stack;
	*stack = new_stack;
}
