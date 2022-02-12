/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackadd_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:38:23 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:01:30 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stacktadd_front(t_elem **stack, t_elem *new_stack)
{
	if (!stack || !new_stack)
		return ;
	if (*stack)
	{
		if ((*stack)->prev == NULL)
			new_stack->prev = *stack;
		else
			new_stack->prev = (*stack)->prev;
		(*stack)->prev = new_stack;
		new_stack->next = *stack;
	}
	*stack = new_stack;
}
