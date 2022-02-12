/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacknew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:35:29 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:36:20 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

t_elem	*stacknew(int nbr)
{
	t_elem	*head;

	head = (t_elem *)malloc(sizeof(t_elem));
	if (!head)
		return (0);
	head->nbr = nbr;
	head->pos = 0;
	head->prev = 0;
	head->next = 0;
	return (head);
}
