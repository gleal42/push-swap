/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:50:12 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:50:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

int	stack_size(t_elem *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}
