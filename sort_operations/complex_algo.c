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

void	execute_moves(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len)
{
	while (cmds->rr > 0)
	{
		op_rr(a, b, max_len);
		(cmds->rr)--;
	}
	while (cmds->ra > 0)
	{
		op_ra(a, b, max_len);
		(cmds->ra)--;
	}
	while (cmds->rrr > 0)
	{
		op_rrr(a, b, max_len);
		(cmds->rrr)--;
	}
	while (cmds->rra > 0)
	{
		op_rra(a, b, max_len);
		(cmds->rra)--;
	}
	if (cmds->ss > 0)
	{
		op_ss(a, b, max_len);
		(cmds->ss)--;
	}
	if (cmds->sa > 0)
	{
		op_sa(a, b, max_len);
		(cmds->sa)--;
	}
	if (cmds->sb > 0)
	{
		op_sb(a, b, max_len);
		(cmds->sb)--;
	}
	if (cmds->pa > 0)
	{
		if ((*a)->pos == lims->max_a)
			(lims->max_a)--;
		if ((*a)->pos == lims->min_a)
			(lims->min_a)++;
		if (!(*b))
		{
			lims->max_b = (*a)->pos;
			lims->min_b = (*a)->pos;
		}
		else
		{
			if ((*a)->pos > lims->max_b)
				lims->max_b = (*a)->pos;
			else if ((*a)->pos < lims->min_b)
				lims->min_b = (*a)->pos;
		}
		op_pa(a, b, max_len);
		(cmds->pa)--;
	}
	while (cmds->rb > 0)
	{
		op_rb(a, b, max_len);
		(cmds->rb)--;
	}
	while (cmds->rrb > 0)
	{
		op_rrb(a, b, max_len);
		(cmds->rrb)--;
	}
}

void	count_total(t_cmds *cmds)
{
	cmds->total = 0;
	cmds->total += cmds->sa;
	cmds->total += cmds->sb;
	cmds->total += cmds->ss;
	cmds->total += cmds->ra;
	cmds->total += cmds->rb;
	cmds->total += cmds->rr;
	cmds->total += cmds->pa;
	cmds->total += cmds->pb;
	cmds->total += cmds->rra;
	cmds->total += cmds->rrb;
	cmds->total += cmds->rrr;
}

t_cmds	find_closest_spot_for_b(t_stack  *cur_b, t_stack  *a, t_all *all)
{
	t_stack 		*forw_a;
	t_stack 		*rev_a;
	t_cmds off;
	t_cmds temp;

	init_cmd_list(&temp);
	if (is_good_position_forward(cur_b, a, all->lims.min_a, all->lims.max_a)
			&& is_good_position_backward(cur_b, a->prev, all->lims.min_a, all->lims.max_a))
	{
		off = prepare_push_b(all->cmds.ra, all->cmds.rra, all->cmds.rb, all->cmds.rrb);
		return (off);
	}
	off = prepare_push_b(all->cmds.ra, all->cmds.rra, all->cmds.rb, all->cmds.rrb);
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
	t_cmds	temp;

	if (!b)
		return ;
	temp = find_closest_spot_for_b(b, a, all);
	all->forw_b = b->next;
	all->rev_b = b->prev;
	while (all->forw_b &&
			(temp.rb < all->cmds.total
		|| temp.rrb < all->cmds.total)) 
	{
		temp = find_closest_spot_for_b(b, a, all);
		if (temp.total < all->cmds.total)
			all->cmds = temp;
		temp.rb++;
		temp.rrb++;
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
	temp->cmds.total = temp->cmds.ra + temp->cmds.rb +temp->cmds.rr + temp->cmds.rra + temp->cmds.rrb +temp->cmds.rrr + temp->cmds.pa;;
	if (!b)
		return ;
	if (!b->next)
	{
		if (tobemoved->nbr > b->nbr)
		{
			has_rb++;
			temp->cmds.rb++;
		}
		else
		{
			has_rrb++;
			temp->cmds.rrb++;
		}
	}
	temp->forw_b = b->next;
	temp->rev_b = b->prev;
	while (!has_rb && !has_rrb && temp->forw_b && temp->rev_b )
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
		fwd_total = temp->cmds.ra + temp->cmds.rb +temp->cmds.rr + temp->cmds.pa;
	if (has_rrb)
		rev_total = temp->cmds.rra + temp->cmds.rrb + temp->cmds.rrr + temp->cmds.pa;
	if ((fwd_total < rev_total && has_rb)|| !has_rrb)
	{
		temp->cmds.rra = 0;
		temp->cmds.rrr = 0;
		temp->cmds.total = fwd_total;
	}
	else if ((fwd_total < rev_total && has_rb) || !has_rrb)
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

	temp.lims.min_a = 1;
	temp.lims.max_a = n;
	temp.lims.min_b = 0;
	temp.lims.max_b = 0;
	temp.forw_a = *a;
	temp.rev_a = *a;
	temp.ini_rot_a.ra = 0;
	temp.ini_rot_a.rra = 0;
	init_cmd_list(&(off.cmds));
	while (1)
	{
		init_cmd_list(&(temp.cmds));
		if (is_good_position_forward(temp.forw_a, (temp.forw_a)->next, temp.lims.min_a, temp.lims.max_a))
		{
			temp.ini_rot_a.ra++;
			temp.forw_a = temp.forw_a->next;
		}
		else
		{
			init_cmd_list(&(temp.cmds));
			temp.cmds.ra = temp.ini_rot_a.ra;
			push_a_moves(*b, &temp, temp.forw_a);
			if (temp.cmds.total < off.cmds.total || !(off.cmds.total))
				off.cmds = temp.cmds;
			temp.ini_rot_a.ra++;
			temp.forw_a = temp.forw_a->next;
		}
		if (is_good_position_backward(temp.rev_a, temp.rev_a->prev, 1, n))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;	
		}
		else
		{
			temp.ini_rot_a.rra++;
			init_cmd_list(&(temp.cmds));
			temp.cmds.rra = temp.ini_rot_a.rra;
			push_a_moves(*b, &temp, temp.rev_a);
			if (temp.cmds.total < off.cmds.total || !(off.cmds.total))
				off.cmds = temp.cmds;
			temp.rev_a = temp.rev_a->prev;	
		}
 		if (off.cmds.total && (off.cmds.total <= temp.ini_rot_a.ra || off.cmds.total <= temp.ini_rot_a.rra))
		{
			execute_moves(&off.cmds, a, b, &temp.lims, max_a);
			temp.forw_a = *a;
			temp.rev_a = *a;
			temp.ini_rot_a.ra = 0;
			temp.ini_rot_a.rra = 0;
			init_cmd_list(&(off.cmds));
		} 
		else if (!temp.forw_a || temp.forw_a->nbr == temp.rev_a->nbr)
			break ;
	}
	widthdraw_b_moves(*a, *b, &temp);
}
