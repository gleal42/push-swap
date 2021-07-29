/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:33:38 by gleal             #+#    #+#             */
/*   Updated: 2021/07/24 17:31:41by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

t_cmds	prepare_push_b(int ra, int rra, int rb, int rrb)
{
	t_cmds cmds;
	
	cmds.sa=0;
	cmds.sb=0;
	cmds.ss=0;
	cmds.pa=0;
	cmds.pb=0;
	cmds.ra=0;
	cmds.rb=0;
	cmds.rr=0;
	cmds.rra=0;
	cmds.rrb=0;
	cmds.rrr=0;
	if (ra && rb)
	{
		if (ra >= rb)
		{
			cmds.rr = rb;
			cmds.ra = ra - rb;
		}
		else
		{
			cmds.rr = ra;
			cmds.rb = rb - ra;
		}
	}
	if (rra && rrb)
	{
		if (rra >= rrb)
		{
			cmds.rr = rb;
			cmds.ra = ra - rb;
		}
		else
		{
			cmds.rr = ra;
			cmds.rb = rb - ra;
		}
	}
	cmds.total = cmds.ra + cmds.rb + cmds.rr + cmds.rra + cmds.rrb + cmds.rrr;
	return (cmds);
}

void	execute_moves(t_cmds *cmds, t_stack **a, t_stack **b, t_limits_a *lim_a, int max_len)
{
	while (cmds->rr)
	{
		op_rr(a, b, max_len);
		(cmds->rr)--;
	}
	while (cmds->rrr)
	{
		op_rrr(a, b, max_len);
		(cmds->rrr)--;
	}
	if (cmds->pa)
	{
		if ((*a)->pos == lim_a->max_a)
			(lim_a->max_a)--;
		if ((*a)->pos == lim_a->min_a)
			(lim_a->min_a)++;
		op_pa(a, b, max_len);
		(cmds->pa)--;
	}
/* 	while (cmds->ss)
	{
		op_ss(a, b, max_len);
		cmds->ss;
	}
	cmds->sa;
	cmds->sb;
	cmds->ra;
	cmds->rb;
	cmds->rr;
	cmds->pa;
	cmds->pb;
	cmds->rra;
	cmds->rrb;
	cmds->rrr; */
}

void	count_total(t_all *temp)
{
	temp->temp_cmds.total = 0;
	temp->temp_cmds.total += temp->temp_cmds.sa;
	temp->temp_cmds.total += temp->temp_cmds.sb;
	temp->temp_cmds.total += temp->temp_cmds.ss;
	temp->temp_cmds.total += temp->temp_cmds.ra;
	temp->temp_cmds.total += temp->temp_cmds.rb;
	temp->temp_cmds.total += temp->temp_cmds.rr;
	temp->temp_cmds.total += temp->temp_cmds.pa;
	temp->temp_cmds.total += temp->temp_cmds.pb;
	temp->temp_cmds.total += temp->temp_cmds.rra;
	temp->temp_cmds.total += temp->temp_cmds.rrb;
	temp->temp_cmds.total += temp->temp_cmds.rrr;
}

t_cmds	find_closest_spot_for_b(t_stack  *cur_b, t_stack  *a, t_all *all)
{
	t_stack 		*forw_a;
	t_stack 		*rev_a;
	t_cmds off;
	t_cmds temp;

	init_cmd_list(&temp);
	if (is_good_position_forward(cur_b, a, all->lim_a.min_a, all->lim_a.max_a)
			&& is_good_position_backward(cur_b, a->prev, all->lim_a.min_a, all->lim_a.max_a))
	{
		off = prepare_push_b(all->temp_cmds.ra, all->temp_cmds.rra, all->temp_cmds.rb, all->temp_cmds.rrb);
		return (off);
	}
	off = prepare_push_b(all->temp_cmds.ra, all->temp_cmds.rra, all->temp_cmds.rb, all->temp_cmds.rrb);
	return (off);
	forw_a = a;
	rev_a = a;
/* 	while (forw_a)
	{
		forw_a->next;	
		rev_a->prev;
	} */
}

void	widthdraw_b_moves(t_stack *a, t_stack *b, t_all *all)
{
	if (!b)
		return ;
	all->cmds = find_closest_spot_for_b(b, a, all);
	all->forw_b = b->next;
	all->rev_b = b->prev;
	while (all->forw_b &&
			(all->temp_cmds.rb < all->cmds.total
		|| all->temp_cmds.rrb < all->cmds.total)) 
	{
		all->temp_cmds = find_closest_spot_for_b(b, a, all);
		if (all->temp_cmds.total < all->cmds.total)
			all->cmds = all->temp_cmds;
		all->temp_cmds.rb++;
		all->temp_cmds.rrb++;
	}
}

void	push_a_moves(t_stack *b, t_all *temp, t_stack *tobemoved)
{
	int has_rb;
	int has_rrb;
	int rev_total;
	int fwd_total;

	has_rb = 0;
	has_rrb = 0;
	fwd_total = 0;
	rev_total = 0;
	temp->cmds.pa++;
	temp->cmds.total = 1;
	if (!b)
		return ;
	if (!b->next && (tobemoved->nbr > b->nbr))
	{
		has_rb++;
		temp->cmds.rb++;
	}
	temp->forw_b = b->next;
	temp->rev_b = b->prev;
	while (!has_rb && !has_rrb)
	{
		if((temp->cmds.ra)-- > 0)
			temp->cmds.rr++;
		else
			temp->cmds.rb++;
		if((temp->cmds.rra)-- > 0)
			temp->cmds.rrr++;
		else
			temp->cmds.rrb++;
		if (is_good_position_forward(tobemoved, temp->forw_b, stack_last(b)->pos, b->pos))
			has_rb++;
		if (is_good_position_backward(tobemoved, temp->rev_b, stack_last(b)->pos, b->pos))
			has_rrb++;
		temp->rev_b = (temp->rev_b)->prev;
		temp->forw_b = (temp->forw_b)->next;
	}
	if (has_rb)
		fwd_total = temp->cmds.ra + temp->cmds.rr + temp->cmds.pa;
	if (has_rrb)
		rev_total = temp->cmds.rra + temp->cmds.rrr + temp->cmds.pa;
	if (fwd_total < rev_total || !has_rrb)
	{
		temp->cmds.rra = 0;
		temp->cmds.rrr = 0;
		temp->cmds.total = fwd_total;
	}
	else if (fwd_total < rev_total || !has_rrb)
	{
		temp->cmds.ra = 0;
		temp->cmds.rr = 0;
		temp->cmds.total = rev_total;
	}
}

/*
** Combines 3 techniques to get the numbers in the right order:
** 		1 - In case there are numbers in b check if there's a good
** opportunity to push from b to a
** 		2 - In case we find a number:
** 			2.1 In case we can swap a number nearby we do it
** 			2.2 In case there are no numbers nearby to swap push to B
** 				(rotating b to push it in the right place)
** @param:	- [t_stack *] a
**			- [t_stack *] b
** Line-by-line comments:
** @line-line	comment
*/
	
void	more_complex_algorithm(t_stack **a, t_stack **b, int max_a, int n)
{
	t_all off;
	t_all temp;

	temp.lim_a.min_a = 1;
	temp.lim_a.max_a = n;
	temp.forw_a = *a;
	temp.rev_a = *a;
	temp.ini_rot_a.ra = 0;
	temp.ini_rot_a.rra = 0;
	init_cmd_list(&(off.cmds));
	while (1)
	{
		if (is_good_position_forward(temp.forw_a, (temp.forw_a)->next, temp.lim_a.min_a, temp.lim_a.max_a))
		{
			temp.ini_rot_a.ra++;
			temp.forw_a = temp.forw_a->next;
			if (temp.forw_a->nbr == temp.rev_a->nbr)
				break ;
		}
		else
		{
			init_cmd_list(&(temp.cmds));
			temp.temp_cmds.ra = temp.ini_rot_a.ra;
			push_a_moves(*b, &temp, temp.forw_a);
			if (temp.cmds.total < off.cmds.total || !(off.cmds.total))
				off.cmds = temp.cmds;
		}
		if (is_good_position_backward(temp.rev_a, temp.rev_a->prev, 1, n))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;	
			if (temp.forw_a->nbr == temp.rev_a->nbr)
				break ;
		}
		else
		{
			init_cmd_list(&(temp.temp_cmds));
			temp.temp_cmds.rra = temp.ini_rot_a.rra;
			push_a_moves(*b, &temp, temp.rev_a);
			if (temp.cmds.total < off.cmds.total)
				off.cmds = temp.cmds;
		}
 		if (off.cmds.total && (off.cmds.total <= temp.ini_rot_a.ra || off.cmds.total <= temp.ini_rot_a.rra))
		{
			execute_moves(&off.cmds, a, b, &temp.lim_a, max_a);
			temp.forw_a = *a;
			temp.rev_a = *a;
			init_cmd_list(&(off.cmds));
			init_cmd_list(&(temp.cmds));
		} 
	}
	widthdraw_b_moves(*a, *b, &temp);
}
