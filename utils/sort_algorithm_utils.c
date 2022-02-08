/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:01:10 by gleal             #+#    #+#             */
/*   Updated: 2022/02/08 19:50:33 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	find_rotation_direction(t_all *all, int *rotation_direction)
{
	while (!(*rotation_direction) && all->forw_a)
	{
		if (all->forw_a->pos == 1)
			(*rotation_direction) = RA;
		else if (all->rev_a->pos == 1)
			(*rotation_direction) = RRA;
		if (all->forw_a->pos == all->rev_a->pos)
			break ;
		all->forw_a = all->forw_a->next;
		if (all->forw_a->pos == all->rev_a->pos)
			break ;
		all->rev_a = all->rev_a->prev;
	}
	if (!(*rotation_direction))
		return ;
}