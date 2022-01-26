/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_rotate_fwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2022/01/26 16:44:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "operations.h"

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
