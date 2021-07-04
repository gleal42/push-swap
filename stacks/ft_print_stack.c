/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:38:46 by gleal             #+#    #+#             */
/*   Updated: 2021/07/04 16:36:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void ft_print_stack(t_stack *stack)
{
	int i;

	i = 0;
	while (stack)
	{
		printf("%d\n", stack->nbr);
		stack = stack->next;
		i++;
	}
}
