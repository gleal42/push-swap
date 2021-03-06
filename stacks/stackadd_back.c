/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:32:18 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:34:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	elem_add_back(t_elem **stack, t_elem *new_stack)
{
	t_elem	*head;

	head = *stack;
	if (!stack || !new_stack)
		return ;
	if (!*stack)
	{
		*stack = new_stack;
		return ;
	}
	head->prev = new_stack;
	while (head->next)
		head = head->next;
	head->next = new_stack;
	new_stack->prev = head;
}
