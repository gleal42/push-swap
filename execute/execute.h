/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:38:34 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:29:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "push_swap.h"

// execute_moves.c

void	execute_moves(t_cmds *cmds, t_stack *a, t_stack *b);
void	execute_pb_backward(t_cmds *cmds, t_stack *a, t_stack *b);
void	execute_pb_forward(t_cmds *cmds, t_stack *a, t_stack *b);
void	execute_swap_forward(t_cmds *cmds, t_elem **a, t_elem **b);
void	execute_swap_backward(t_cmds *cmds, t_elem **a, t_elem **b);

// execute_moves2.c

void	execute_merge_ab(t_cmds *cmds, t_stack *a, t_stack *b);
void	rotate_until_sorted(t_all *all);

// execute_utils.c

void	find_rotation_direction(t_all *all, int *rotation_direction);

#endif
