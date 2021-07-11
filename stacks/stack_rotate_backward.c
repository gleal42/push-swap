/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate_backward.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 21:17:46 by gleal             #+#    #+#             */
/*   Updated: 2021/07/11 16:05:38 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stacks.h"

void	stack_rotate_backward(t_stack **stack)
{
	t_stack	*first_stack;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	(*stack)->prev->next = *stack;
	first_stack = (*stack)->next;
	(*stack)->next = 0;
	*stack = first_stack;
}

/* void	stack_rotate_backward(t_stack **stack)
{
	t_stack	*last_stack;
	t_stack	*scd_to_last_stack;

	last_stack = *stack;
	*stack = (*stack)->next;
	scd_to_last_stack = stack_last(*stack);
	scd_to_last_stack->next = last_stack;	
	last_stack->next = 0;
}
 */