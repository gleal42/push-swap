/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:43:16 by gleal             #+#    #+#             */
/*   Updated: 2021/07/15 22:14:26by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int	is_stack_sorted(t_stack **a, int n)
{
	t_stack *temp_cur;
	t_stack *temp_next;

	temp_cur = *a;
	temp_next = (*a)->next;
	while (temp_next)
	{
		if (temp_next->pos == 1)
		{
			if (temp_cur->pos != n)
				return (0);
		}
		else
		{
			if (temp_next->pos < temp_cur->pos)
				return (0);
		}
		temp_cur = temp_cur->next;
		temp_next = temp_next->next;
	}	
	return (1);
}

void	rotate_until_sorted(t_stack **a, t_stack **b, int max_len)
{
	int rotation_direction;

	t_stack *norm;
	t_stack *rev;
	rotation_direction = 0;

	norm = (*a)->next;
	rev = (*a)->prev;
	while (!rotation_direction && norm)
	{
		if (norm->pos == 1)
			rotation_direction = RA;
		else if (rev->pos == 1)
			rotation_direction = RRA;
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
	}
}

void	ft_sort_stacks(t_stack **a, t_stack **b, int max_len, int n)
{
	if (*a == 0 || (*a)->next == 0)
		return ;
	if (is_stack_sorted(a, n))
	{
		if ((*a)->pos == 1)
			return ;
		else
			rotate_until_sorted(a, b, max_len);
	}
	else 
		more_complex_algorithm(a, b, max_len, n);
}

// replace rotate_until_sorted by basic algorithm