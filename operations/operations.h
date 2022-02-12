/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:38 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:01:30 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "structs.h"
# include "stacks.h"

// operations_push_swap.c

int	op_sa(t_elem **a, t_elem **b);
int	op_sb(t_elem **a, t_elem **b);
int	op_ss(t_elem **a, t_elem **b);
int	op_pb(t_elem **a, t_elem **b);
int	op_pa(t_elem **a, t_elem **b);

// operations_rotate_bwd.c

int	op_rrb(t_elem **a, t_elem **b);
int	op_rrr(t_elem **a, t_elem **b);
int	op_rra(t_elem **a, t_elem **b);

// operations_rotate_fwd.c

int	op_ra(t_elem **a, t_elem **b);
int	op_rb(t_elem **a, t_elem **b);
int	op_rr(t_elem **a, t_elem **b);

#endif