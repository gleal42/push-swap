/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:38:23 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:38:25 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	ft_stacktadd_front(t_stack **stack, t_stack *new_stack)
{
	if (!stack || !new_stack)
		return ;
	if (*stack)
		new_stack->next = *stack;
	*stack = new_stack;
}
