/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2021/07/05 21:34:13 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		op_rra(t_stack **a)
{
	stack_rotate_backward(a);
	ft_putstr_fd("rra\n", 1);
	return (0);
}

int		op_rrb(t_stack **b)
{
	stack_rotate_backward(b);
	ft_putstr_fd("rrb\n", 1);
	return (0);
}

int		op_rrr(t_stack **a, t_stack **b)
{
	stack_rotate_backward(a);
	stack_rotate_backward(b);
	ft_putstr_fd("rrr\n", 1);
	return (0);
}
