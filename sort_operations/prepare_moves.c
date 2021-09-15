/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:56:33 by gleal             #+#    #+#             */
/*   Updated: 2021/09/15 22:55:29 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

void	merge_ramp_spot(t_stack *a, t_stack *b, t_all *temp, t_stack *firstinramp)
{
	t_cmds start_push;
	t_stack	*first_nbr;

	first_nbr = firstinramp->prev;
	start_push = temp->cmds;
	while (continue_ramp_analysis(a, first_nbr, temp))
	{
		first_nbr = first_nbr->prev;
	}
	place_in_b(b, temp, firstinramp);
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

void	find_closest_b_spot(t_stack  *cur_b, t_stack  *a, t_all *temp, int max)
{
	int good_spot_forward;
	int good_spot_reverse;
	int rev_total;
	int fwd_total;

	init_cmd_list(&temp->cmds);
	good_spot_forward = 0;
	good_spot_reverse = 0;
	fwd_total = 0;
	rev_total = 0;
	temp->cmds.rb = temp->ini_rot_b.rb;
	temp->cmds.rrb = temp->ini_rot_b.rrb;
	temp->cmds.pb++;
	temp->cmds.total = count_moves(&temp->cmds);
	if (!a)
		return ;
	if (!a->next)
	{
		if (cur_b->nbr > a->nbr)
		{
			good_spot_forward++;
			temp->cmds.ra++;
		}
		else
			good_spot_reverse++;
	}
	if (is_next_nbr_bigger(cur_b, a, temp->lims.min_a, temp->lims.max_a)
			&& is_prev_nbr_smaller(cur_b, a->prev, temp->lims.min_a, temp->lims.max_a))
		return ;
	temp->forw_a = a->next;
	temp->rev_a = a->prev->prev;
	fwd_total = temp->cmds.total;
	rev_total = temp->cmds.total;
	while (!good_spot_forward && !good_spot_reverse && temp->forw_a)
	{
		if(temp->cmds.rb > 0)
		{	
			temp->cmds.rb--;
			temp->cmds.rr++;
		}
		else
		{
			temp->cmds.ra++;
			fwd_total++;
		}
		if(temp->cmds.rrb > 0)
		{
			temp->cmds.rrb--;
			temp->cmds.rrr++;
		}
		else
		{
			temp->cmds.rra++;
			rev_total++;
		}
		if (max && (fwd_total >= max && rev_total >= max))
		{
			init_cmd_list(&temp->cmds);
			return ;
		}
		if (is_next_nbr_bigger(cur_b, temp->forw_a, temp->lims.min_a, temp->lims.max_a)
				&& is_prev_nbr_smaller(cur_b, temp->forw_a->prev, temp->lims.min_a, temp->lims.max_a))
			good_spot_forward++;
		if (temp->rev_a->next)
		{
			if (is_prev_nbr_smaller(cur_b, temp->rev_a, temp->lims.min_a, temp->lims.max_a)
				&& is_next_nbr_bigger(cur_b, temp->rev_a->next, temp->lims.min_a, temp->lims.max_a))
				good_spot_reverse++;
		}
		else
		{
			if (is_prev_nbr_smaller(cur_b, temp->rev_a, temp->lims.min_a, temp->lims.max_a)
				&& is_next_nbr_bigger(cur_b, a, temp->lims.min_a, temp->lims.max_a))
				good_spot_reverse++;
		}
		temp->rev_a = (temp->rev_a)->prev;
		temp->forw_a = (temp->forw_a)->next;
	}
	if (!good_spot_forward && !good_spot_reverse)
	{
			printf("\033[0;34m📌 Here in %s line %d\n\033[0m", __FILE__, __LINE__);
			init_cmd_list(&temp->cmds);
			return ;
	}
	if (good_spot_forward && (fwd_total <= rev_total || !good_spot_reverse))
	{
		temp->cmds.rra = 0;
		temp->cmds.rrr = 0;
		temp->cmds.total = fwd_total;
	}
	else if (good_spot_reverse && (rev_total <= fwd_total || !good_spot_reverse))
	{
		temp->cmds.ra = 0;
		temp->cmds.rr = 0;
		temp->cmds.total = rev_total;
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
		off->rev_b = off->rev_b->prev;
	}
}