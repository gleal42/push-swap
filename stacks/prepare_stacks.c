/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:21:20 by gleal             #+#    #+#             */
/*   Updated: 2022/02/07 00:51:12 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	prepare_stack_a(t_stack **a, char **stack_a_args)
{
	t_stack	*next_nbr;
	int		nbr;
	int		i;

	i = 0;
	while (stack_a_args[i])
	{
		nbr = ft_atoi(stack_a_args[i]);
		if (is_nbr_in_stack(nbr, *a))
		{
			stacks_clear(a, delete_stack);
			ft_putstr_fd("Error\n", 2);
			exit(EXIT_FAILURE);
		}
		next_nbr = stacknew(nbr);
		if (!next_nbr)
		{
			stacks_clear(a, delete_stack);
			ft_putstr_fd("Error\n", 2);
			exit(EXIT_FAILURE);
		}
		stackadd_back(a, next_nbr);
		i++;
	}
}
