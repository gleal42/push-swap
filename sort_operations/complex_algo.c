/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:33:38 by gleal             #+#    #+#             */
/*   Updated: 2021/07/20 23:08:33 by gleal            ###   ########.fr       */
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
	all->off_cmds = find_closest_spot_for_b(b, a, all);
	all->forw_b = b->next;
	all->rev_b = b->prev;
	while (all->forw_b &&
			(all->temp_cmds.rb < all->off_cmds.total
		|| all->temp_cmds.rrb < all->off_cmds.total)) 
	{
		all->temp_cmds = find_closest_spot_for_b(b, a, all);
		if (all->temp_cmds.total < all->off_cmds.total)
			all->off_cmds = all->temp_cmds;
		all->temp_cmds.rb++;
		all->temp_cmds.rrb++;
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
	temp.lim_a.max_a = max_a;
	while (1)
	{
		init_cmd_list(&(temp.temp_cmds));
		if (temp.ini_rot_a.ra == 0 && temp.ini_rot_a.rra == 0)
			widthdraw_b_moves(*a, *b, &temp);
		if (is_good_position_forward(temp.forw_a, temp.forw_a->next, 1, n))
		{
			temp.ini_rot_a.ra++;
			temp.forw_a = temp.forw_a->next;
		}
		if (temp.forw_a->nbr == temp.rev_a->nbr)
			break ;
		if (is_good_position_backward(temp.rev_a, temp.rev_a->prev, 1, n))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;	
		}
		if (temp.forw_a->nbr == temp.rev_a->nbr)
			break ;
		off = temp;
/* 		if (executed commands)
		{
			temp.forw_a = *a;
			temp.rev_a = *a;
		} */
	}
}

/* 	int rotation_direction;

	t_stack *norm;
	t_stack *rev;
	rotation_direction = 0;

	norm = (*a)->next;
	rev = (*a)->prev;
	while (!rotation_direction && norm)
	{
		if (norm->pos == 1)
			rotation_direction = RRA;
		else if (rev->pos == 1)
			rotation_direction = RA;
		if (norm->pos == rev->pos)
			break ;
		norm = norm->next;
		if (norm->pos == rev->pos)
			break ;
		rev = rev->prev;	
	}
	if (!rotation_direction)
		return ;
	while ((*a)->pos != 1)
	{
		if (rotation_direction == RA)
			op_ra(a, b, max_len);
		else if (rotation_direction == RRA)
			op_rra(a, b, max_len);
	} */
