/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:45 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 17:03:10 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

t_stack	*ft_stackmap(t_stack *stack, void *(*f)(void *), void (*del)(void *))
{
	t_stack	*first_s;
	t_stack	*new_s;

	if (!stack || !f)
		return (0);
	first_s = 0;
	while (stack)
	{
		new_s = ft_stacknew(f(stack->nbr));
		if (!new_s)
		{
			ft_stackclear(&first_s, del);
			return (0);
		}
		ft_stackadd_back(&first_s, new_s);
		stack = stack->next;
	}
	return (first_s);
}
