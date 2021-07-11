/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:54:25 by gleal             #+#    #+#             */
/*   Updated: 2021/07/11 16:34:34 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		op_ra(t_stack **a, int max_len)
{
	stack_rotate_forward(a);
	ft_putstr_fd("ra\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_rb(t_stack **b, int max_len)
{
	stack_rotate_forward(b);
	ft_putstr_fd("rb\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}

int		op_rr(t_stack **a, t_stack **b, int max_len)
{
	stack_rotate_forward(a);
	stack_rotate_forward(b);
	ft_putstr_fd("rr\n", 1);
	print_both_stacks(*a, *b, max_len);
	return (0);
}
