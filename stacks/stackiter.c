/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:46:33 by gleal             #+#    #+#             */
/*   Updated: 2021/07/04 16:03:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stackiter(t_stack *stack, void (*f)(int))
{
	if (!stack || !f)
		return ;
	while (stack)
	{
		f(stack->nbr);
		stack = stack->next;
	}
}
