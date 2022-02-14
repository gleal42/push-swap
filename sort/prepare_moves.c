/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:46:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/14 15:57:12 by gleal            ###   ########.fr       */
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

void	merge_ramp_spot(t_all *all, t_all *temp, t_elem *firstinramp)
{
	all->a.ramp.first_nbr = firstinramp;
	all->a.ramp.init_cmds = temp->exec_cmds;
	all->a.ramp.off_nbr = firstinramp;
	ft_bzero(&(all->a.ramp.best_cmds), sizeof(t_cmds));
	while (1)
	{
		predict_merge_moves(all, temp, firstinramp);
		if (is_better_ramp(all->a.ramp.init_cmds, all->a.ramp.best_cmds))
		{
			all->a.ramp.best_cmds = all->a.ramp.init_cmds;
			all->a.ramp.off_nbr = all->a.ramp.first_nbr;
		}
		not_rotate_fwd(&temp->exec_cmds);
		all->a.ramp.init_cmds = temp->exec_cmds;
		if ((all->a.ramp.first_nbr->prev)->pos == firstinramp->pos
			|| (!continue_ramp_analysis(all->a.head, all->a.ramp.first_nbr, temp)))
			break ;
		all->a.ramp.first_nbr = all->a.ramp.first_nbr->prev;
	}
	temp->exec_cmds.ra = all->a.ramp.best_cmds.ra;
	temp->exec_cmds.ra += all->a.ramp.best_cmds.rr;
	temp->exec_cmds.rra = all->a.ramp.best_cmds.rra;
	temp->exec_cmds.rra += all->a.ramp.best_cmds.rrr;
	place_in_b(all->b.head, temp, all->a.ramp.off_nbr);
}

/*
	quando chega ao final do loop (aquilo que aconteceu no rotate basico)
	talvez preciso acrescentar mais uma verificacao
*/

void	place_in_b(t_elem *b, t_all *temp, t_elem *tobemoved)
{
	int	closer_fwd;
	int	closer_bwd;

	closer_fwd = 0;
	closer_bwd = 0;
	init_push_b(temp);
	if (is_good_to_place_no_rot_b(b, tobemoved, temp->b.lims))
		return ;
	temp->b.forw = b->next;
	temp->b.rev = b->prev->prev;
	while (!closer_fwd && !closer_bwd && temp->b.forw)
	{
		add_double_rots_a(&temp->exec_cmds);
		check_if_found_rot(temp, tobemoved, &closer_fwd, &closer_bwd);
		temp->b.forw = (temp->b.forw)->next;
		temp->b.rev = (temp->b.rev)->prev;
	}
	calculate_initial_pushmoves(closer_fwd, closer_bwd, &temp->exec_cmds);
}

void	swap_a(t_all *temp, t_elem *firstinramp, t_elem *a)
{
	(void)firstinramp;
	if (temp->exec_cmds.ra)
		temp->exec_cmds.type = SWAP_FWD;
	else
		temp->exec_cmds.type = SWAP_BWD;
	temp->exec_cmds.sa = 1;
	temp->exec_cmds.total = count_moves(&temp->exec_cmds);
	if (!a || !a->next)
		return ;
	if (!a->next->next && a->pos < a->next->pos)
	{
		temp->exec_cmds.sa = 0;
		temp->exec_cmds.ss = 1;
	}
}

void	min_push_b_to_a_moves(t_elem *a, t_elem *b, t_all *off)
{
	t_all	temp;

	temp = *off;
	ft_bzero(&temp.b.ini_rot, sizeof(t_rot));
	if (!b)
		return ;
	find_closest_b_spot(b, a, &temp, off->exec_cmds.total);
	off->exec_cmds = temp.exec_cmds;
	off->b.forw = b->next;
	off->b.rev = b->prev;
	while (off->b.forw && (temp.b.ini_rot.r < off->exec_cmds.total
			|| temp.b.ini_rot.rrev < off->exec_cmds.total))
	{
		ft_bzero(&temp.exec_cmds, sizeof(t_cmds));
		temp.b.ini_rot.rrev = 0;
		temp.b.ini_rot.r++;
		find_closest_b_spot(off->b.forw, a, &temp, off->exec_cmds.total);
		if (temp.exec_cmds.total
			&& (temp.exec_cmds.total < off->exec_cmds.total))
			off->exec_cmds = temp.exec_cmds;
		off->b.forw = off->b.forw->next;
		ft_bzero(&temp.exec_cmds, sizeof(t_cmds));
		temp.b.ini_rot.rrev = temp.b.ini_rot.r;
		temp.b.ini_rot.r = 0;
		find_closest_b_spot(off->b.rev, a, &temp, off->exec_cmds.total);
		if (temp.exec_cmds.total
			&& (temp.exec_cmds.total < off->exec_cmds.total))
			off->exec_cmds = temp.exec_cmds;
		temp.b.ini_rot.r = temp.b.ini_rot.rrev;
		off->b.rev = off->b.rev->prev;
	}
}
