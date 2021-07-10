/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate_forward.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:31:55 by gleal             #+#    #+#             */
/*   Updated: 2021/07/05 20:34:24 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stacks.h"

void	stack_rotate_forward(t_stack **stack)
{
	t_stack	*second_stack;

	second_stack = *stack;
	(*stack)->prev->next = 0;
	*stack = (*stack)->prev;
	(*stack)->next = second_stack;
}

/* void	stack_rotate_forward(t_stack **stack)
{
	t_stack	*last_stack;
	t_stack	*first_stack;

	last_stack = stack_second_to_last(*stack);
	first_stack = last_stack->next;
	last_stack->next = 0;
	first_stack->next = *stack;
	*stack = first_stack;
}
 */