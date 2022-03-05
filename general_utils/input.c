/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:16:45 by gleal             #+#    #+#             */
/*   Updated: 2022/03/05 17:47:13 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	add_positions(t_elem	**a, int n)
{
	t_elem		*first;
	t_elem		*next_min;
	int			i;

	i = 1;
	first = (*a);
	while (i <= n)
	{
		*a = first;
		next_min = 0;
		while (*a)
		{
			if (! (*a)->pos
				&& (next_min == 0 || ((*a)->nbr < next_min->nbr)))
				next_min = *a;
			*a = (*a)->next;
		}
		*a = next_min;
		(*a)->pos = i;
		i++;
	}
	*a = first;
}

int	count_moves(t_cmds *cmds)
{
	int	total;

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

int	is_input_integer(char **stack_a_args)
{
	int	i;

	i = 0;
	while (stack_a_args[i])
	{
		if (!is_integer(stack_a_args[i]))
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	nbr_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i])
		i++;
	return (i);
}
