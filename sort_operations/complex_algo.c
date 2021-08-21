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


int	count_moves(t_cmds *cmds)
{
	int total;

	total = 0;
	total += cmds->sa;
	total += cmds->sb;
	total += cmds->ss;
	total += cmds->ra;
	total += cmds->rb;
	total += cmds->rr;
	total += cmds->pa;
	total += cmds->pb;
	total += cmds->rra;
	total += cmds->rrb;
	total += cmds->rrr;
	return (total);
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
	if (is_good_position_forward(cur_b, a, temp->lims.min_a, temp->lims.max_a)
			&& is_good_position_backward(cur_b, a->prev, temp->lims.min_a, temp->lims.max_a))
		return ;
	temp->forw_a = a->next;
	temp->rev_a = a->prev;
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
		if (is_good_position_forward(cur_b, temp->forw_a, temp->lims.min_a, temp->lims.max_a)
				&& is_good_position_backward(cur_b, temp->forw_a->prev, temp->lims.min_a, temp->lims.max_a))
			good_spot_forward++;
		if (temp->rev_a->next)
		{
			if (is_good_position_backward(cur_b, temp->rev_a, temp->lims.min_a, temp->lims.max_a)
				&& is_good_position_forward(cur_b, temp->rev_a->next, temp->lims.min_a, temp->lims.max_a))
				good_spot_reverse++;
		}
		else
		{
			if (is_good_position_backward(cur_b, temp->rev_a, temp->lims.min_a, temp->lims.max_a)
				&& is_good_position_forward(cur_b, a, temp->lims.min_a, temp->lims.max_a))
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

void	push_a_moves(t_stack *b, t_all *temp, t_stack *tobemoved)
{
	int has_rb;
	int has_rrb;
	int rev_total;
	rev_total = 0;

	temp->cmds.type = INITIAL_PUSH;
	has_rb = 0;
	has_rrb = 0;
	temp->cmds.pa++;
	temp->cmds.total = temp->cmds.ra + temp->cmds.rb +temp->cmds.rr + temp->cmds.rra + temp->cmds.rrb +temp->cmds.rrr + temp->cmds.pa;;
	if (!b)
		return ;
	if (!b->next)
	{
		if (tobemoved->pos < b->pos)
		{
			temp->cmds.rb++;
			has_rb++;
		}
		else
			has_rrb++;
		calculate_initial_pushmoves(has_rb, has_rrb, &temp->cmds);
		return ;
	}
	if (is_good_position_forward(tobemoved, b, temp->lims.min_b, temp->lims.max_b)
			&& is_good_position_backward(tobemoved, b->prev, temp->lims.min_b, temp->lims.max_b))
			has_rb++;
	temp->forw_b = b->next;
	temp->rev_b = b->prev->prev;
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
	if (is_good_position_forward(tobemoved, temp->forw_b, temp->lims.min_b, temp->lims.max_b)
			&& is_good_position_backward(tobemoved, temp->forw_b->prev, temp->lims.min_b, temp->lims.max_b))
			has_rb++;
		if (is_good_position_backward(tobemoved, temp->rev_b, temp->lims.min_b, temp->lims.max_b)
			&& is_good_position_forward(tobemoved, temp->rev_b->next, temp->lims.min_b, temp->lims.max_b))
			has_rrb++;
		temp->forw_b = (temp->forw_b)->next;
		temp->rev_b = (temp->rev_b)->prev;
	}
	calculate_initial_pushmoves(has_rb, has_rrb, &temp->cmds);
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
	while (temp.forw_a)
	{
		init_cmd_list(&(temp.cmds));
		if (is_good_position_forward(temp.forw_a, (temp.forw_a)->next, temp.lims.min_a, temp.lims.max_a)
			|| temp.forw_a->pos == temp.lims.max_a)
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
		if (is_good_position_backward(temp.rev_a, temp.rev_a->prev, temp.lims.min_a, temp.lims.max_a))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;	
		}
		else
		{
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
		else if (!temp.forw_a || temp.forw_a->pos == temp.rev_a->pos)
			break ;
	}
	temp.forw_a = *a;
	temp.rev_a = *a;
	temp.ini_rot_a.ra = 0;
	temp.ini_rot_a.rra = 0;
	while (*b)
	{
		init_cmd_list(&(temp.cmds));
		min_push_b_to_a_moves(*a, *b, &temp);
		execute_merge_ab(&temp.cmds, a, b, &temp.lims, max_a);
	}
	if (is_stack_sorted(a, n))
	{
		if ((*a)->pos == 1)
			return ;
		else
			rotate_until_sorted(a, b, max_a);
	}
	else
		printf("WHOOPSIE\n");
}
