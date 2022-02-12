/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:16:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

t_elem	*stackmap(t_elem *stack, int (*f)(int), void (*del)(int *))
{
	t_elem	*first_s;
	t_elem	*new_s;

	if (!stack || !f)
		return (0);
	first_s = 0;
	while (stack)
	{
		new_s = stacknew(f(stack->nbr));
		if (!new_s)
		{
			stack_clear(&first_s, del);
			return (0);
		}
		elem_add_back(&first_s, new_s);
		stack = stack->next;
	}
	return (first_s);
}
