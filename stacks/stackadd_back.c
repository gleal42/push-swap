/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:32:18 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:34:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stackadd_back(t_stack **stack, t_stack *new_stack)
{
	t_stack	*head;

	head = *stack;
	if (!stack || !new_stack)
		return ;
	if (!*stack)
	{
		*stack = new_stack;
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new_stack;
}
