/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:17:08 by gleal             #+#    #+#             */
/*   Updated: 2021/07/03 16:21:36 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		op_sa(t_list **a)
{
	ft_lstswap(a);
	ft_putstr_fd("sa\n", 1);
}

int		op_sb(t_list **b)
{
	ft_lstswap(b);
	ft_putstr_fd("sb\n", 1);
}
