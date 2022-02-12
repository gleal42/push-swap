/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 16:17:51 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:01:30 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	stack_push_from_to(t_elem **original, t_elem **destination)
{
	t_elem	*temp;

	temp = *original;
	*original = (*original)->next;
	if (*original)
	{
		if ((*original)->next)
			(*original)->prev = temp->prev;
		else
			(*original)->prev = 0;
	}
	temp->next = 0;
	temp->prev = 0;
	stacktadd_front(destination, temp);
}
