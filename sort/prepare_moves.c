/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:56:33 by gleal             #+#    #+#             */
/*   Updated: 2021/12/19 22:23:55y gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort.h"

/* 
	existe um commit anterior em que merge ramp spot estava diferente (ver nome dos commits e ver se vale a pena voltar)
	Adicionar o predict_a só para o primeiro numero (para ter conta os ra e rra substituirem por rr e rrr)
	Mandou mal o maior número (pôs num sitio aleatório)
*/

void	merge_ramp_spot(t_stack *a, t_stack *b, t_all *temp, t_stack *firstinramp)
{
	t_cmds init_cmds;
	t_cmds best_cmds;
	t_cmds off_cmds;
	t_stack	*first_nbr;
	t_stack	*off_nbr;

	first_nbr = firstinramp;
	init_cmds = temp->cmds;
	off_cmds = init_cmds;
	off_nbr = firstinramp;
	init_cmd_list(&best_cmds);
	while (1)
	{
		predict_merge_moves(first_nbr, firstinramp, a, b, &init_cmds, temp);
		if (is_better_ramp(init_cmds, best_cmds))
		{
			best_cmds = init_cmds;
			if (off_cmds.ra)
				best_cmds.ra = off_cmds.ra;
			else if (off_cmds.rra)
				best_cmds.rra = off_cmds.rra;
			off_nbr = first_nbr;
		}
		if (off_cmds.ra)
			off_cmds.ra--;
		else if (off_cmds.rra || !off_cmds.ra)
			off_cmds.rra++;
		init_cmds=off_cmds; 
		if ((first_nbr->prev)->pos == firstinramp->pos ||
			(!continue_ramp_analysis(a, first_nbr, temp)))
			break ;
		first_nbr = first_nbr->prev;
	}
	off_cmds.ra = best_cmds.ra;
	off_cmds.rra = best_cmds.rra;
	temp->cmds = off_cmds;
	place_in_b(b, temp, off_nbr);
}

void	place_in_b(t_stack *b, t_all *temp, t_stack *tobemoved)
{
	int has_rb;
	int has_rrb;
	int rev_total;
	rev_total = 0;

	has_rb = 0;
	has_rrb = 0;
	if (temp->cmds.ra)
		temp->cmds.type = PUSH_B_FWD;
	else 
		temp->cmds.type = PUSH_B_BWD;
	temp->cmds.pb++;
	temp->cmds.total = temp->cmds.ra + temp->cmds.rb +temp->cmds.rr + temp->cmds.rra + temp->cmds.rrb +temp->cmds.rrr + temp->cmds.pb;
	if (!b)
		return ;
	if (!b->next)
	{
		has_rb++;
		calculate_initial_pushmoves(has_rb, has_rrb, &temp->cmds);
			return ;
	}
	if (is_next_nbr_bigger(tobemoved, b->prev, temp->lims.min_b, temp->lims.max_b)
			&& is_prev_nbr_smaller(tobemoved, b, temp->lims.min_b, temp->lims.max_b))
	{
		if (temp->cmds.ra || (!temp->cmds.ra && !temp->cmds.rra))
			has_rb++;
		else if (temp->cmds.rra)
			has_rrb++;
	}
	temp->forw_b = b->next;
	temp->rev_b = b->prev->prev;
	while (!has_rb && !has_rrb && temp->forw_b && temp->rev_b )
	{
		if(temp->cmds.ra > 0)
		{
			temp->cmds.ra--;
			temp->cmds.rr++;
		}
		else
			temp->cmds.rb++;
		if(temp->cmds.rra > 0)
		{
			temp->cmds.rra--;
			temp->cmds.rrr++;
		}
		else
			temp->cmds.rrb++;
	if (is_next_nbr_bigger(tobemoved, temp->forw_b->prev, temp->lims.min_b, temp->lims.max_b)
			&& is_prev_nbr_smaller(tobemoved, temp->forw_b, temp->lims.min_b, temp->lims.max_b))
			has_rb++;
		if (is_next_nbr_bigger(tobemoved, temp->rev_b, temp->lims.min_b, temp->lims.max_b)
		 && is_prev_nbr_smaller(tobemoved, temp->rev_b->next, temp->lims.min_b, temp->lims.max_b))
			has_rrb++;
		temp->forw_b = (temp->forw_b)->next;
		temp->rev_b = (temp->rev_b)->prev;
	}
	calculate_initial_pushmoves(has_rb, has_rrb, &temp->cmds);
}



void	swap_a(t_all *temp, t_stack *firstinramp, t_stack *b)
{
	(void)firstinramp;
	if (temp->cmds.ra)
		temp->cmds.type = SWAP_FWD;
	else 
		temp->cmds.type = SWAP_BWD;
	temp->cmds.sa = 1;
	temp->cmds.total = count_moves(&temp->cmds);
	if (!b || !b->next)
		return ;
	if (!b->next->next && b->pos < b->next->pos)
	{
		temp->cmds.sa = 0;
		temp->cmds.ss = 1;
	}
}

void	min_push_b_to_a_moves(t_stack *a, t_stack *b, t_all *off)
{
	t_all	temp;

	temp = *off;
	temp.ini_rot_b.rb = 0;
	temp.ini_rot_b.rrb = 0;
	if (!b)
		return ;
	find_closest_b_spot(b, a, &temp, off->cmds.total);
	off->cmds = temp.cmds;
	off->forw_b = b->next;
	off->rev_b = b->prev;
	while (off->forw_b &&
			(temp.ini_rot_b.rb < off->cmds.total
		|| temp.ini_rot_b.rrb < off->cmds.total)) 
	{
		init_cmd_list(&temp.cmds);
		temp.ini_rot_b.rrb = 0;
		temp.ini_rot_b.rb++;
		find_closest_b_spot(off->forw_b, a, &temp, off->cmds.total);
		if (temp.cmds.total && (temp.cmds.total < off->cmds.total))
			off->cmds = temp.cmds;
		off->forw_b = off->forw_b->next;
		init_cmd_list(&temp.cmds);
		temp.ini_rot_b.rrb = temp.ini_rot_b.rb;
		temp.ini_rot_b.rb = 0;
		find_closest_b_spot(off->rev_b, a, &temp, off->cmds.total);
		if (temp.cmds.total && (temp.cmds.total < off->cmds.total))
			off->cmds = temp.cmds;
		temp.ini_rot_b.rb = temp.ini_rot_b.rrb;
		off->rev_b = off->rev_b->prev;
	}
}