/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 23:42:18 by gleal             #+#    #+#             */
/*   Updated: 2022/02/06 19:36:03 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validations.h"

int	is_input_integer(char **stack_a_args)
{
	int	i;

	i = 0;
	if (!stack_a_args[0])
		return (0);
	while (stack_a_args[i])
	{
		if (!is_integer(stack_a_args[i]))
		{
			printf("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_nbr_in_stack(int nbr, t_stack *a)
{
	while (a)
	{
		if (a->nbr == nbr)
			return (1);
		a = a->next;
	}
	return (0);
}
