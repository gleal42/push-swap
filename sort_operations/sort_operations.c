/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2021/07/04 17:00:29 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		op_sa(t_stack **a)
{
	ft_stackswap(a);
	ft_putstr_fd("sa\n", 1);
	return (0);
}

int		op_sb(t_stack **b)
{
	ft_stackswap(b);
	ft_putstr_fd("sb\n", 1);
	return (0);
}

int		op_ss(t_stack **a, t_stack **b)
{
	ft_stackswap(a);
	ft_stackswap(b);
	ft_putstr_fd("ss\n", 1);
	return (0);
}

int		op_pa(t_stack **a, t_stack **b)
{
	ft_stack_push_from_to(a, b);
	ft_putstr_fd("pa\n", 1);
	return (0);
}

int		op_pb(t_stack **a, t_stack **b)
{
	ft_stack_push_from_to(b, a);
	ft_putstr_fd("pb\n", 1);
	return (0);
}
