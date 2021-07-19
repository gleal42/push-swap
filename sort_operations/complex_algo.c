/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:33:38 by gleal             #+#    #+#             */
/*   Updated: 2021/07/19 22:16:39 by gleal            ###   ########.fr       */
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
}              

t_cmds	find_closest_spot_for_b(t_stack  *cur_b, t_stack  *a, int rb, int rrb)
{
	t_stack 		*forw_a;
	t_stack 		*rev_a;
	t_cmds off;
	t_cmds temp;

	init_cmd_list(&temp);
	if (is_good_position_forward(b, a, min_a, max_a)
			&& is_good_position_backward(b, a->prev, min_a, max_a))
	{
		off = prepare_push_b(0, 0, rb, rrb);
		return (off);
	}
	forw_a = a;
	rev_a = a;
	while (forw_a)
	{
		forw_a->next;	
		rev_a->prev;
	}
}

t_all	widthdraw_b_moves(t_stack *a, t_stack *b, int min_a, int max_a)
{
	t_cmds off;
	t_cmds temp;
	t_stack 		*forw_b;
	t_stack 		*rev_b;

	init_rot_b(&temp);
	init_cmd_list(&temp);
	if (!b)
		return (temp);
	off = find_closest_spot_for_b(b, a, 0, 0);
	forw_b = b->next;
	rev_b = b->prev;
	while (forw_b && (temp.rb < off.total || temp.rrb < off.total)) 
	{
		temp = find_closest_spot_for_b();
		if (temp.total < off.total)
			off = temp;
		temp.rb++;
		temp.rrb++;
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
	
void	more_complex_algorithm(t_stack **a, t_stack **b, int max_len, int n)
{
	t_all off;
	t_all temp;

	init_rot_a(&temp);
	while ()
	{
		init_cmd_list(&temp);
		if (temp.ini_rot_a.ra == 0 && temp.ini_rot_a.rra == 0)
			temp = widthdraw_b_moves(a, b, min_a, max_a);
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
		if (/*executed commands*/)
		{
			temp.forw_a = *a;
			temp.rev_a = *a;
		}
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
