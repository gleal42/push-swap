/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_a_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:46:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/02 02:20:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	analyze_fwd(t_all **all)
{
	if (is_smaller_than((*all)->a.forw, ((*all)->a.forw)->next,
			(*all)->a.lims.min, (*all)->a.lims.max))
		(*all)->a.ini_rot.r++;
	else
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, (*all)->a.forw, (*all)->a.lims.min,
				(*all)->a.lims.max))
		{
			(*all)->pred_cmds.ra = (*all)->a.ini_rot.r;
			swap_a(*all, (*all)->a.head);
			(*all)->a.ini_rot.r++;
		}
		else
		{
			(*all)->a.ini_rot.r++;
			(*all)->pred_cmds.ra = (*all)->a.ini_rot.r;
			merge_ramp_spot(*all, (*all)->a.forw->next);
		}
		update_exec_cmds(all);
	}
	(*all)->a.forw = (*all)->a.forw->next;
}

void	analyze_bwd(t_all **all)
{
	if (is_bigger_than((*all)->a.rev, (*all)->a.rev->prev,
			(*all)->a.lims.min, (*all)->a.lims.max))
		(*all)->a.ini_rot.rrev++;
	else
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, (*all)->a.rev->prev,
				(*all)->a.lims.min, (*all)->a.lims.max))
		{
			(*all)->a.ini_rot.rrev++;
			(*all)->pred_cmds.rra = (*all)->a.ini_rot.rrev;
			swap_a(*all, (*all)->a.head);
		}
		else
		{
			(*all)->pred_cmds.rra = (*all)->a.ini_rot.rrev;
			merge_ramp_spot(*all, (*all)->a.rev);
			(*all)->a.ini_rot.rrev++;
		}
		update_exec_cmds(all);
	}
	(*all)->a.rev = (*all)->a.rev->prev;
}

void	merge_ramp_spot(t_all *all, t_elem *firstinramp)
{
	all->a.ramp.first_nbr = firstinramp;
	all->a.ramp.init_cmds = all->pred_cmds;
	all->a.ramp.off_nbr = firstinramp;
	ft_bzero(&(all->a.ramp.best_cmds), sizeof(t_cmds));
	while (1)
	{
		pred_ramp_moves(all, firstinramp);
		if (is_better_ramp(all->a.ramp.init_cmds, all->a.ramp.best_cmds))
		{
			all->a.ramp.best_cmds = all->a.ramp.init_cmds;
			all->a.ramp.off_nbr = all->a.ramp.first_nbr;
		}
		ramp_start_before(&all->pred_cmds);
		all->a.ramp.init_cmds = all->pred_cmds;
		if ((all->a.ramp.first_nbr->prev)->pos == firstinramp->pos)
			break ;
		all->a.ramp.first_nbr = all->a.ramp.first_nbr->prev;
	}
	all->pred_cmds.ra = all->a.ramp.best_cmds.ra;
	all->pred_cmds.ra += all->a.ramp.best_cmds.rr;
	all->pred_cmds.rra = all->a.ramp.best_cmds.rra;
	all->pred_cmds.rra += all->a.ramp.best_cmds.rrr;
	place_in_b_rots(all->b.head, all, all->a.ramp.off_nbr, &all->pred_cmds);
	add_update_cmd(&all->pred_cmds.pb, &all->pred_cmds, 1);
}

/*
	quando chega ao final do loop (aquilo que aconteceu no rotate basico)
	talvez preciso acrescentar mais uma verificacao
	while (!all->b.near_rot.r && !all->b.near_rot.rrev && all->b.forw)
	retirar break se deixar de funcionar
*/

void	place_in_b_rots(t_elem *b, t_all *all, t_elem *move, t_cmds *cmds)
{
	all->b.near_rot.r = 0;
	all->b.near_rot.rrev = 0;
	init_push_b(cmds);
	if (is_good_to_place_wo_rot_b(b, move, all->b.lims))
		return ;
	init_stacks_iteration(&all->b, b);
	iterate_fwd_rev_toend(&all->b);
	while (all->b.forw)
	{
		add_double_rots_a(cmds);
		check_if_found_rot_a(move, &all->b, &all->b.near_rot, all->b.lims);
		if (all->b.near_rot.r || all->b.near_rot.rrev)
			break ;
		iterate_fwd_rev_toend(&all->b);
	}
	calculate_initial_pb_moves(all->b.near_rot.r, all->b.near_rot.rrev, cmds);
}

void	swap_a(t_all *all, t_elem *a)
{
	if (all->pred_cmds.ra)
		all->pred_cmds.type = SWAP_FWD;
	else
		all->pred_cmds.type = SWAP_BWD;
	all->pred_cmds.sa = 1;
	all->pred_cmds.total = count_moves(&all->pred_cmds);
	if (!a || !a->next)
		return ;
	if (!a->next->next && a->pos < a->next->pos)
	{
		all->pred_cmds.sa = 0;
		all->pred_cmds.ss = 1;
	}
}
