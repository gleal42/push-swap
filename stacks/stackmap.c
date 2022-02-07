/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/04 17:13:24 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

t_stack	*stackmap(t_stack *stack, int(*f)(int), void (*del)(int *))
{
	t_stack	*first_s;
	t_stack	*new_s;

	if (!stack || !f)
		return (0);
	first_s = 0;
	while (stack)
	{
		new_s = stacknew(f(stack->nbr));
		if (!new_s)
		{
			stacks_clear(&first_s, del);
			return (0);
		}
		stackadd_back(&first_s, new_s);
		stack = stack->next;
	}
	return (first_s);
}
