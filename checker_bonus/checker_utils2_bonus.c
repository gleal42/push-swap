/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:59:40 by gleal             #+#    #+#             */
/*   Updated: 2022/03/05 17:01:46 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	swap_both_stacks(t_elem **a, t_elem **b)
{
	stack_swap(a);
	stack_swap(b);
}

void	rot_back_both_stacks(t_elem **a, t_elem **b)
{
	stack_rotate_backward(a);
	stack_rotate_backward(b);
}

void	rot_fwd_both_stacks(t_elem **a, t_elem **b)
{
	stack_rotate_forward(a);
	stack_rotate_forward(b);
}

void	create_cmd_list(const char **all_cmds)
{
	all_cmds[0] = "sa";
	all_cmds[1] = "sb";
	all_cmds[2] = "ss";
	all_cmds[3] = "ra";
	all_cmds[4] = "rb";
	all_cmds[5] = "rr";
	all_cmds[6] = "pa";
	all_cmds[7] = "pb";
	all_cmds[8] = "rra";
	all_cmds[9] = "rrb";
	all_cmds[10] = "rrr";
	all_cmds[11] = 0;
}

void	delete_string(void *str)
{
	free(str);
	str = NULL;
}
