/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:40:45 by gleal             #+#    #+#             */
/*   Updated: 2021/07/05 20:38:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stacks_clear(t_stack **stack, void (*del)(int))
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
