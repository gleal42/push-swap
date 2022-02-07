/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:40:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/04 17:12:34 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stacks_clear(t_stack **stack, void (*del)(int *))
{
	t_stack	*deleter;

	if (!stack || !del || !*stack)
		return ;
	while (*stack)
	{
		deleter = *stack;
		*stack = (*stack)->next;
		stackdelone(deleter, del);
	}
	*stack = 0;
}
