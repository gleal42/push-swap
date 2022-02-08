#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "structs.h"
# include "stacks.h"

// operations_push_swap.c

int	op_sa(t_stack **a, t_stack **b, int max_len);
int	op_sb(t_stack **a, t_stack **b, int max_len);
int	op_ss(t_stack **a, t_stack **b, int max_len);
int	op_pb(t_stack **a, t_stack **b, int max_len);
int	op_pa(t_stack **a, t_stack **b, int max_len);

// operations_rotate_bwd.c

int	op_rrb(t_stack **a, t_stack **b, int max_len);
int	op_rrr(t_stack **a, t_stack **b, int max_len);
int	op_rra(t_stack **a, t_stack **b, int max_len);

// operations_rotate_fwd.c

int	op_ra(t_stack **a, t_stack **b, int max_len);
int	op_rb(t_stack **a, t_stack **b, int max_len);
int	op_rr(t_stack **a, t_stack **b, int max_len);

#endif