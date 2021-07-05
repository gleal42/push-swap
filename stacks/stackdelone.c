/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:42:46 by gleal             #+#    #+#             */
/*   Updated: 2021/07/04 16:02:10 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stackdelone(t_stack *stack, void (*del)(int))
{
	if (!stack || !del)
		return ;
	del(stack->nbr);
	free(stack);
}
