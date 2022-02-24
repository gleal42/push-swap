/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_a_b_mvs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:30:22 by gleal             #+#    #+#             */
/*   Updated: 2022/02/24 00:33:47 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	place_in_a(t_elem *a, t_elem *b, t_all *all)
{
	t_all	temp;

	temp = *all;
	if (!b)
		return ;
	find_closest_b_spot(b, a, &temp, all->pred_cmds.total);
	all->pred_cmds = temp.pred_cmds;
	iterate_fwd_rev_toend(&all->b);
	while (all->b.forw && (temp.b.ini_rot.r < all->pred_cmds.total
			|| temp.b.ini_rot.rrev < all->pred_cmds.total))
	{
		temp.b.ini_rot.rrev++;
		temp.b.ini_rot.r++;
		place_in_a_fwd(a, all, &temp);
		place_in_a_bwd(a, all, &temp);
		iterate_fwd_rev_toend(&all->b);
	}
}

void	place_in_a_fwd(t_elem *a, t_all *all, t_all *temp)
{
	ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
	all->pred_cmds.rb = all->b.ini_rot.r;
	find_closest_b_spot(all->b.forw, a, temp, all->pred_cmds.total);
	if (temp->pred_cmds.total
		&& (temp->pred_cmds.total < all->pred_cmds.total))
		all->pred_cmds = temp->pred_cmds;
}

void	place_in_a_bwd(t_elem *a, t_all *all, t_all *temp)
{
	ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
	all->pred_cmds.rrb = all->b.ini_rot.rrev;
	find_closest_b_spot(all->b.rev, a, temp, all->pred_cmds.total);
	if (temp->pred_cmds.total
		&& (temp->pred_cmds.total < all->pred_cmds.total))
		all->pred_cmds = temp->pred_cmds;
}
