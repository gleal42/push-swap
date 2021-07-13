/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 21:43:16 by gleal             #+#    #+#             */
/*   Updated: 2021/07/13 22:45:46 by gleal            ###   ########.fr       */
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

void	ft_sort_stacks(t_stack **a, t_stack **b, int max_len, int n)
{
	t_cmd_list cmds;

	if (*a == 0 || (*a)->next == 0)
		return ;
	if (is_stack_sorted(a, n))
	{
		if ((*a)->pos == 1)
			return ;
/* 		else
			rotate_until_sorted(*a) */
	}
	else if (is_stack_sorted(a, n) && *b == 0)
	init_cmd_list(&cmds);
	op_pa(a,b, max_len);
}
