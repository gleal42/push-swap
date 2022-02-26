/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_a_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:30:22 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:30:59 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	place_in_a(t_all *all)
{
	t_all	temp;

	temp = *all;
	if (!all->b.head)
		return ;
	find_spot_for_cur_b(all->b.head, &temp, all->pred_cmds.total);
	all->pred_cmds = temp.pred_cmds;
	init_stacks_iteration(&all->b, all->b.head);
	iterate_fwd_rev_toend(&all->b);
	while (all->b.forw && (temp.b.ini_rot.r < all->pred_cmds.total
			|| temp.b.ini_rot.rrev < all->pred_cmds.total))
	{
		temp.b.ini_rot.rrev++;
		temp.b.ini_rot.r++;
		place_in_a_fwd(all, &temp);
		place_in_a_bwd(all, &temp);
		iterate_fwd_rev_toend(&all->b);
	}
}

void	place_in_a_fwd(t_all *all, t_all *temp)
{
	ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
	temp->pred_cmds.rb = temp->b.ini_rot.r;
	find_spot_for_cur_b(all->b.forw, temp, all->pred_cmds.total);
	if (temp->pred_cmds.total
		&& (temp->pred_cmds.total < all->pred_cmds.total))
		all->pred_cmds = temp->pred_cmds;
}

void	place_in_a_bwd(t_all *all, t_all *temp)
{
	ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
	temp->pred_cmds.rrb = temp->b.ini_rot.rrev;
	find_spot_for_cur_b(all->b.rev, temp, all->pred_cmds.total);
	if (temp->pred_cmds.total
		&& (temp->pred_cmds.total < all->pred_cmds.total))
		all->pred_cmds = temp->pred_cmds;
}

void	find_spot_for_cur_b(t_elem *cur_b, t_all *temp, int max)
{
	int	fwd_total;
	int	rev_total;

	init_find_closest_b_spot(temp);
	if (is_good_to_place_wo_rot_a(temp->a.head, cur_b, temp->a.lims))
		return ;
	fwd_total = temp->pred_cmds.total;
	rev_total = fwd_total;
	init_stacks_iteration(&temp->a, temp->a.head);
	while (!temp->a.near_rot.r && !temp->a.near_rot.rrev)
	{
		iterate_fwd_rev_noend(&temp->a, temp->a.head);
		add_double_rots_b(&temp->pred_cmds, &fwd_total,
			&rev_total);
		if (max && (fwd_total >= max && rev_total >= max))
		{
			ft_bzero(&temp->pred_cmds, sizeof(t_cmds));
			return ;
		}
		check_if_found_rot_b(cur_b, temp);
	}
	calculate_initial_pa_moves(temp->a.near_rot.r,
		temp->a.near_rot.rrev, &temp->pred_cmds);
}
