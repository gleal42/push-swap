/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:46:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 00:45:49 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* 
	existe um commit anterior em que merge ramp spot
	estava diferente (ver nome dos commits e ver se vale a pena voltar)
	Adicionar o predict_a só para o primeiro numero 
	(para ter conta os ra e rra substituirem por rr e rrr)
	Mandou mal o maior número (pôs num sitio aleatório)
	tinha isto a seguir ao
	(...)
	best_cmds = init_cmds;
	if (off_cmds.ra)
		best_cmds.ra = off_cmds.ra;
	else if (off_cmds.rra)
		best_cmds.rra = off_cmds.rra;
*/

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
		if ((all->a.ramp.first_nbr->prev)->pos == firstinramp->pos
			|| (!continue_ramp_analysis(all->a.head,
					all->a.ramp.first_nbr, all)))
			break ;
		all->a.ramp.first_nbr = all->a.ramp.first_nbr->prev;
	}
	all->pred_cmds.ra = all->a.ramp.best_cmds.ra;
	all->pred_cmds.ra += all->a.ramp.best_cmds.rr;
	all->pred_cmds.rra = all->a.ramp.best_cmds.rra;
	all->pred_cmds.rra += all->a.ramp.best_cmds.rrr;
	place_in_b(all->b.head, all, all->a.ramp.off_nbr);
}

/*
	quando chega ao final do loop (aquilo que aconteceu no rotate basico)
	talvez preciso acrescentar mais uma verificacao
*/

void	place_in_b(t_elem *b, t_all *all, t_elem *tobemoved)
{
	int	closer_fwd;
	int	closer_bwd;

	closer_fwd = 0;
	closer_bwd = 0;
	init_push_b(all);
	if (is_good_to_place_wo_rot_b(b, tobemoved, all->b.lims))
		return ;
	all->b.forw = b->next;
	all->b.rev = b->prev->prev;
	while (!closer_fwd && !closer_bwd && all->b.forw)
	{
		add_double_rots_a(&all->pred_cmds);
		check_if_found_rot(all, tobemoved, &closer_fwd, &closer_bwd);
		all->b.forw = (all->b.forw)->next;
		all->b.rev = (all->b.rev)->prev;
	}
	calculate_initial_pushmoves(closer_fwd, closer_bwd, &all->pred_cmds);
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

void	min_push_b_to_a_moves(t_elem *a, t_elem *b, t_all *off)
{
	t_all	temp;

	temp = *off;
	ft_bzero(&temp.b.ini_rot, sizeof(t_rot));
	if (!b)
		return ;
	find_closest_b_spot(b, a, &temp, off->pred_cmds.total);
	off->pred_cmds = temp.pred_cmds;
	off->b.forw = b->next;
	off->b.rev = b->prev;
	while (off->b.forw && (temp.b.ini_rot.r < off->pred_cmds.total
			|| temp.b.ini_rot.rrev < off->pred_cmds.total))
	{
		ft_bzero(&temp.pred_cmds, sizeof(t_cmds));
		temp.b.ini_rot.rrev = 0;
		temp.b.ini_rot.r++;
		find_closest_b_spot(off->b.forw, a, &temp, off->pred_cmds.total);
		if (temp.pred_cmds.total
			&& (temp.pred_cmds.total < off->pred_cmds.total))
			off->pred_cmds = temp.pred_cmds;
		off->b.forw = off->b.forw->next;
		ft_bzero(&temp.pred_cmds, sizeof(t_cmds));
		temp.b.ini_rot.rrev = temp.b.ini_rot.r;
		temp.b.ini_rot.r = 0;
		find_closest_b_spot(off->b.rev, a, &temp, off->pred_cmds.total);
		if (temp.pred_cmds.total
			&& (temp.pred_cmds.total < off->pred_cmds.total))
			off->pred_cmds = temp.pred_cmds;
		temp.b.ini_rot.r = temp.b.ini_rot.rrev;
		off->b.rev = off->b.rev->prev;
	}
}
