/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate_backward.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 21:17:46 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 01:10:17 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stack_rotate_backward(t_elem **stack)
{
	t_elem	*first_stack;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	(*stack)->prev->next = *stack;
	first_stack = (*stack)->next;
	(*stack)->next = 0;
	*stack = first_stack;
}
