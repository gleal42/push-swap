/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:46:36 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:31:12 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	find_rotation_direction(t_all *all, int *rotation_direction)
{
	while (!(*rotation_direction) && all->a.forw)
	{
		if (all->a.forw->pos == 1)
			(*rotation_direction) = RA;
		else if (all->a.rev->pos == 1)
			(*rotation_direction) = RRA;
		if (all->a.forw->pos == all->a.rev->pos)
			break ;
		all->a.forw = all->a.forw->next;
		if (all->a.forw->pos == all->a.rev->pos)
			break ;
		all->a.rev = all->a.rev->prev;
	}
	if (!(*rotation_direction))
		return ;
}
