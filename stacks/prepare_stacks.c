/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:21:20 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 16:10:21 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

int	prepare_stack_a(t_elem **a, char **stack_a_args)
{
	t_elem	*next_nbr;
	int		nbr;
	int		i;

	i = 0;
	while (stack_a_args[i])
	{
		nbr = ft_atoi(stack_a_args[i]);
		if (is_nbr_in_stack(nbr, *a))
		{
			stack_clear(a, delete_stack);
			ft_putstr_fd("Error\n", 2);
			return(EXIT_FAILURE);
		}
		next_nbr = stacknew(nbr);
		if (!next_nbr)
		{
			stack_clear(a, delete_stack);
			ft_putstr_fd("Error\n", 2);
			return(EXIT_FAILURE);
		}
		elem_add_back(a, next_nbr);
		i++;
	}
	return (0);
}
