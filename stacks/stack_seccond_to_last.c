/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_seccond_to_last.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:48:43 by gleal             #+#    #+#             */
/*   Updated: 2021/07/05 20:56:07 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

t_stack	*stack_second_to_last(t_stack *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (lst);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}
