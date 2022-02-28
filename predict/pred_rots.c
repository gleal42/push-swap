/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pred_rots.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 23:25:04 by gleal             #+#    #+#             */
/*   Updated: 2022/02/27 14:48:33 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	update_pred_lims_b(t_all *all, t_lims *lims_b, t_elem *check)
{
	int		min;
	int		max;
	t_elem	*temp;

	temp = all->b.head;
	min = 0;
	max = 0;
	while (temp)
	{
		update_max_min(temp, &min, &max);
		temp = temp->next;
	}
	temp = all->a.ramp.first_nbr;
	while (temp && temp->pos != check->pos)
	{
		update_max_min(temp, &min, &max);
		temp = temp->next;
	}
	lims_b->max = max;
	lims_b->min = min;
}

void	update_max_min(t_elem	*temp, int *min, int *max)
{
	if (!(*min) || temp->pos < (*min))
		(*min) = temp->pos;
	if (!(*max) || temp->pos > (*max))
		(*max) = temp->pos;
}
