/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_push_swap.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2022/01/26 16:39:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "operations.h"

int		op_sa(t_stack **a, t_stack **b, int max_len)
{
	stack_swap(a);
	ft_putstr_fd("sa\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_sb(t_stack **a, t_stack **b, int max_len)
{
	stack_swap(b);
	ft_putstr_fd("sb\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_ss(t_stack **a, t_stack **b, int max_len)
{
	stack_swap(a);
	stack_swap(b);
	ft_putstr_fd("ss\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_pb(t_stack **a, t_stack **b, int max_len)
{
	stack_push_from_to(a, b);
	ft_putstr_fd("pb\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_pa(t_stack **a, t_stack **b, int max_len)
{
	stack_push_from_to(b, a);
	ft_putstr_fd("pa\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}
