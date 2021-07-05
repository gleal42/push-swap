/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:17:51 by gleal             #+#    #+#             */
/*   Updated: 2021/07/05 20:37:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stacks.h"

void	stack_push_from_to(t_stack **src, t_stack **dst)
{
	t_stack *temp;

	temp = *src;
	*src = (*src)->next;
	temp->next = 0;
	stacktadd_front(dst, temp);
}
