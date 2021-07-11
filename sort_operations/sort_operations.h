#ifndef SORT_OPERATIONS_H
# define SORT_OPERATIONS_H

# include "push_swap.h"

int		op_sa(t_stack **a, int max_len);
int		op_sb(t_stack **b, int max_len);
int		op_ss(t_stack **a, t_stack **b, int max_len);
int		op_pa(t_stack **a, t_stack **b, int max_len);
int		op_pb(t_stack **a, t_stack **b, int max_len);
int		op_ra(t_stack **a, int max_len);
int		op_rb(t_stack **b, int max_len);
int		op_rr(t_stack **a, t_stack **b, int max_len);
int		op_rra(t_stack **a, int max_len);
int		op_rrb(t_stack **b, int max_len);
int		op_rrr(t_stack **a, t_stack **b, int max_len);

#endif
