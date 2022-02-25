/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_a_b_mvs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:30:22 by gleal             #+#    #+#             */
/*   Updated: 2022/02/25 17:57:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	place_in_a(t_all *all)
{
	t_all	temp;

	temp = *all;
	if (!all->b.head)
		return ;
	find_closest_b_spot(all->b.head, all->a.head, &temp, all->pred_cmds.total);
	all->pred_cmds = temp.pred_cmds;
	init_stacks_iteration(&all->b, all->b.head);
	iterate_fwd_rev_toend(&all->b);
	while (all->b.forw && (temp.b.ini_rot.r < all->pred_cmds.total
			|| temp.b.ini_rot.rrev < all->pred_cmds.total))
	{
		temp.b.ini_rot.rrev++;
		temp.b.ini_rot.r++;
		place_in_a_fwd(all->a.head, all, &temp);
		place_in_a_bwd(all->a.head, all, &temp);
		iterate_fwd_rev_toend(&all->b);
	}
}

void	place_in_a_fwd(t_elem *a, t_all *all, t_all *temp)
{
	ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
	temp->pred_cmds.rb = temp->b.ini_rot.r;
	find_closest_b_spot(all->b.forw, a, temp, all->pred_cmds.total);
	if (temp->pred_cmds.total
		&& (temp->pred_cmds.total < all->pred_cmds.total))
		all->pred_cmds = temp->pred_cmds;
}

void	place_in_a_bwd(t_elem *a, t_all *all, t_all *temp)
{
	ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
	temp->pred_cmds.rrb = temp->b.ini_rot.rrev;
	find_closest_b_spot(all->b.rev, a, temp, all->pred_cmds.total);
	if (temp->pred_cmds.total
		&& (temp->pred_cmds.total < all->pred_cmds.total))
		all->pred_cmds = temp->pred_cmds;
}
