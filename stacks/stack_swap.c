/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:45:09 by gleal             #+#    #+#             */
/*   Updated: 2021/07/04 16:07:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stack_swap(t_elem **head)
{
	t_elem	*second_stack;
	t_elem	*third_stack;

	if (*head == 0 || (*head)->next == 0)
		return ;
	second_stack = *head;
	third_stack = (*head)->next->next;
	*head = (*head)->next;
	if (third_stack)
	{
		third_stack->prev = second_stack;
		(*head)->prev = second_stack->prev;
	}
	else
		(*head)->prev = second_stack;
	second_stack->prev = *head;
	second_stack->next = third_stack;
	(*head)->next = second_stack;
}
