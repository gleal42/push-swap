/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2021/07/11 16:34:41 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		op_rra(t_stack **a, int max_len)
{
	stack_rotate_backward(a);
	ft_putstr_fd("rra\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_rrb(t_stack **b, int max_len)
{
	stack_rotate_backward(b);
	ft_putstr_fd("rrb\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_rrr(t_stack **a, t_stack **b, int max_len)
{
	stack_rotate_backward(a);
	stack_rotate_backward(b);
	ft_putstr_fd("rrr\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}
