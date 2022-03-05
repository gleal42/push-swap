/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate_bwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:10:26 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

int	op_rra(t_elem **a)
{
	stack_rotate_forward(a);
	ft_putstr_fd("rra\n", 1);
	return (0);
}

int	op_rrb(t_elem **b)
{
	stack_rotate_forward(b);
	ft_putstr_fd("rrb\n", 1);
	return (0);
}

int	op_rrr(t_elem **a, t_elem **b)
{
	stack_rotate_forward(a);
	stack_rotate_forward(b);
	ft_putstr_fd("rrr\n", 1);
	return (0);
}
