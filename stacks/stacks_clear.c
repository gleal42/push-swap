/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:40:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:01:30 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stack_clear(t_elem **stack, void (*del)(int *))
{
	t_elem	*deleter;

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
