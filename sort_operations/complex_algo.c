/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:33:38 by gleal             #+#    #+#             */
/*   Updated: 2021/07/17 18:25:36 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"



t_cmd_list	widthdraw_b_moves(t_stack *a, t_stack *b, int max_len, int n)
{
	t_stack *norm;
	t_stack *rev;
	t_cmd_list off;
	t_cmd_list temp;

	init_rot_b(&temp);
	if (!b)
		return (temp);
	while (b)
	{
		init_cmd_list(&temp);
		temp.norm_a = a;
		temp.rev_a = a;
		b = b->next;
	}
}

void	more_complex_algorithm(t_stack **a, t_stack **b, int max_len, int n)
{
	t_cmd_list off;
	t_cmd_list temp;

	temp.norm_a = *a;
	temp.rev_a = *a;
	init_rot_a(&temp);
	while (1)
	{
		init_cmd_list(&temp);
		if (temp.ini_rot_a.ra == 0 && temp.ini_rot_a.rra == 0)
			temp = widthdraw_b_moves(a, b, max_len, n);

		if (temp.norm_a->next->nbr > temp.norm_a->nbr || (temp.norm_a->pos == n && temp.norm_a->next->pos == 1))
		{
			temp.ini_rot_a.ra++;
			temp.norm_a = temp.norm_a->next;
		}
		if (temp.norm_a->nbr == temp.rev_a->nbr)
			break ;
		if (temp.rev_a->prev->nbr > temp.rev_a->nbr || (temp.rev_a->pos != 1 && temp.rev_a->prev->pos == n))
		{
			temp.ini_rot_a.rra++;
			temp.rev_a = temp.rev_a->prev;	
		}
		if (temp.norm_a->nbr == temp.rev_a->nbr)
			break ;
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
