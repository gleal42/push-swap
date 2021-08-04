/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2021/08/04 20:55:57 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		op_ra(t_stack **a, t_stack **b, int max_len)
{
	stack_rotate_backward(a);
	ft_putstr_fd("ra\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_rb(t_stack **a, t_stack **b, int max_len)
{
	stack_rotate_backward(b);
	ft_putstr_fd("rb\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_rr(t_stack **a, t_stack **b, int max_len)
{
	stack_rotate_backward(a);
	stack_rotate_backward(b);
	ft_putstr_fd("rr\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}
