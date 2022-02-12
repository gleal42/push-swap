/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:38 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 17:39:24 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "structs.h"
# include "stacks.h"

// operations_push_swap.c

int	op_sa(t_stack **a, t_stack **b);
int	op_sb(t_stack **a, t_stack **b);
int	op_ss(t_stack **a, t_stack **b);
int	op_pb(t_stack **a, t_stack **b);
int	op_pa(t_stack **a, t_stack **b);

// operations_rotate_bwd.c

int	op_rrb(t_stack **a, t_stack **b);
int	op_rrr(t_stack **a, t_stack **b);
int	op_rra(t_stack **a, t_stack **b);

// operations_rotate_fwd.c

int	op_ra(t_stack **a, t_stack **b);
int	op_rb(t_stack **a, t_stack **b);
int	op_rr(t_stack **a, t_stack **b);

#endif