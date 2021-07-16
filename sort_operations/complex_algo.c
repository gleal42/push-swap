/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 22:33:38 by gleal             #+#    #+#             */
/*   Updated: 2021/07/16 23:31:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		widthdraw_b_moves(t_stack **a, t_stack **b, int max_len, int n)
{
	if (!(*b))
		return (0);	
}

void	more_complex_algorithm(t_stack **a, t_stack **b, int max_len, int n)
{
	t_stack *norm;
	t_stack *rev;
	int ra;
	int rra;
	int min_moves;
	
	ra = 0;
	rra = 0;
	norm = *a;
	rev = *a;
	while (norm->next)
	{
		min_moves = widthdraw_b_moves(a, b, max_len, n);
		if (norm->next->pos > norm->nbr + 1 || (norm->pos == n && norm->next->pos == 1))

		if (norm->next->nbr > norm->nbr || (norm->pos == n && norm->next->pos == 1))
		{
			ra++;
			norm = norm->next;
		}
		else
		{
			min_moves = 
		}
		if (norm->nbr == rev->nbr)
			break ;
		if (rev->prev->nbr > rev->nbr || (rev->pos != 1 && rev->prev->pos == n))
		{
			rra++;
			rev = rev->prev;	
		}
		if (norm->nbr == rev->nbr)
			break ;
		if (min_moves < 0)
		{

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
