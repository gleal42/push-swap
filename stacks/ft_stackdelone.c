/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:42:46 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:43:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	ft_stackdelone(t_stack *stack, void (*del)(void*))
{
	if (!stack || !del)
		return ;
	del(stack->nbr);
	free(stack);
}
