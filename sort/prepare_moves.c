/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:46:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 20:51:58 by gleal            ###   ########.fr       */
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

void	merge_ramp_spot(t_all *all, t_all *temp, t_stack *firstinramp)
{
	all->ramp.first_nbr = firstinramp;
	all->ramp.init_cmds = temp->exec_cmds;
	all->ramp.off_nbr = firstinramp;
	ft_bzero(&(all->ramp.best_cmds), sizeof(t_cmds));
	while (1)
	{
		predict_merge_moves(all, temp, firstinramp);
		if (is_better_ramp(all->ramp.init_cmds, all->ramp.best_cmds))
		{
			all->ramp.best_cmds = all->ramp.init_cmds;
			all->ramp.off_nbr = all->ramp.first_nbr;
		}
		not_rotate_fwd(&temp->exec_cmds);
		all->ramp.init_cmds = temp->exec_cmds;
		if ((all->ramp.first_nbr->prev)->pos == firstinramp->pos
			|| (!continue_ramp_analysis(all->a, all->ramp.first_nbr, temp)))
			break ;
		all->ramp.first_nbr = all->ramp.first_nbr->prev;
	}
	temp->exec_cmds.ra = all->ramp.best_cmds.ra;
	temp->exec_cmds.rra = all->ramp.best_cmds.rra;
	place_in_b(all->b, temp, all->ramp.off_nbr);
}

/*
	quando chega ao final do loop (aquilo que aconteceu no rotate basico)
	talvez preciso acrescentar mais uma verificacao
*/

void	place_in_b(t_stack *b, t_all *temp, t_stack *tobemoved)
{
	int	closer_fwd;
	int	closer_bwd;

	closer_fwd = 0;
	closer_bwd = 0;
	init_push_b(temp);
	if (is_good_to_place_no_rot_b(b, tobemoved, temp->lims))
		return ;
	temp->forw_b = b->next;
	temp->rev_b = b->prev->prev;
	while (!closer_fwd && !closer_bwd && temp->forw_b)
	{
		add_double_rots_a(&temp->exec_cmds);
		check_if_found_rot(temp, tobemoved, &closer_fwd, &closer_bwd);
		temp->forw_b = (temp->forw_b)->next;
		temp->rev_b = (temp->rev_b)->prev;
	}
	calculate_initial_pushmoves(closer_fwd, closer_bwd, &temp->exec_cmds);
}

void	swap_a(t_all *temp, t_stack *firstinramp, t_stack *a)
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

void	min_push_b_to_a_moves(t_stack *a, t_stack *b, t_all *off)
{
	t_all	temp;

	temp = *off;
	ft_bzero(&temp.ini_rot_b, sizeof(t_rot_b));
	if (!b)
		return ;
	find_closest_b_spot(b, a, &temp, off->exec_cmds.total);
	off->exec_cmds = temp.exec_cmds;
	off->forw_b = b->next;
	off->rev_b = b->prev;
	while (off->forw_b && (temp.ini_rot_b.rb < off->exec_cmds.total
			|| temp.ini_rot_b.rrb < off->exec_cmds.total))
	{
		ft_bzero(&temp.exec_cmds, sizeof(t_cmds));
		temp.ini_rot_b.rrb = 0;
		temp.ini_rot_b.rb++;
		find_closest_b_spot(off->forw_b, a, &temp, off->exec_cmds.total);
		if (temp.exec_cmds.total
			&& (temp.exec_cmds.total < off->exec_cmds.total))
			off->exec_cmds = temp.exec_cmds;
		off->forw_b = off->forw_b->next;
		ft_bzero(&temp.exec_cmds, sizeof(t_cmds));
		temp.ini_rot_b.rrb = temp.ini_rot_b.rb;
		temp.ini_rot_b.rb = 0;
		find_closest_b_spot(off->rev_b, a, &temp, off->exec_cmds.total);
		if (temp.exec_cmds.total
			&& (temp.exec_cmds.total < off->exec_cmds.total))
			off->exec_cmds = temp.exec_cmds;
		temp.ini_rot_b.rb = temp.ini_rot_b.rrb;
		off->rev_b = off->rev_b->prev;
	}
}
