/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:46:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 19:47:00 by gleal            ###   ########.fr       */
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
	int	has_rb;
	int	has_rrb;
	int	rev_total;

	rev_total = 0;
	has_rb = 0;
	has_rrb = 0;
	if (temp->exec_cmds.ra)
		temp->exec_cmds.type = PUSH_B_FWD;
	else
		temp->exec_cmds.type = PUSH_B_BWD;
	temp->exec_cmds.pb++;
	temp->exec_cmds.total = temp->exec_cmds.ra + temp->exec_cmds.rb
		+ temp->exec_cmds.rr + temp->exec_cmds.rra + temp->exec_cmds.rrb
		+ temp->exec_cmds.rrr + temp->exec_cmds.pb;
	if (!b)
		return ;
	if (!b->next)
	{
		has_rb++;
		calculate_initial_pushmoves(has_rb, has_rrb, &temp->exec_cmds);
		return ;
	}
	if (is_next_nbr_bigger(tobemoved, b->prev,
			temp->lims.min_b, temp->lims.max_b)
		&& is_prev_nbr_smaller(tobemoved, b,
			temp->lims.min_b, temp->lims.max_b))
	{
		if (temp->exec_cmds.ra || (!(temp->exec_cmds.ra) && !(temp->exec_cmds.rra)))
			has_rb++;
		else if (temp->exec_cmds.rra)
			has_rrb++;
	}
	temp->forw_b = b->next;
	temp->rev_b = b->prev->prev;
	while (!has_rb && !has_rrb && temp->forw_b && temp->rev_b)
	{
		if (temp->exec_cmds.ra > 0)
		{
			temp->exec_cmds.ra--;
			temp->exec_cmds.rr++;
		}
		else
			temp->exec_cmds.rb++;
		if (temp->exec_cmds.rra > 0)
		{
			temp->exec_cmds.rra--;
			temp->exec_cmds.rrr++;
		}
		else
			temp->exec_cmds.rrb++;
		if (is_next_nbr_bigger(tobemoved, temp->forw_b->prev,
				temp->lims.min_b, temp->lims.max_b)
			&& is_prev_nbr_smaller(tobemoved, temp->forw_b,
				temp->lims.min_b, temp->lims.max_b))
			has_rb++;
		if (is_next_nbr_bigger(tobemoved, temp->rev_b,
				temp->lims.min_b, temp->lims.max_b)
			&& is_prev_nbr_smaller(tobemoved, temp->rev_b->next,
				temp->lims.min_b, temp->lims.max_b))
			has_rrb++;
		temp->forw_b = (temp->forw_b)->next;
		temp->rev_b = (temp->rev_b)->prev;
	}
	calculate_initial_pushmoves(has_rb, has_rrb, &temp->exec_cmds);
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
