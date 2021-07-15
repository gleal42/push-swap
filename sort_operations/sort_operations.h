#ifndef SORT_OPERATIONS_H
# define SORT_OPERATIONS_H

# include "push_swap.h"

# define RA 1
# define RRA 2

int		op_sa(t_stack **a, t_stack **b, int max_len);
int		op_sb(t_stack **a, t_stack **b, int max_len);
int		op_ss(t_stack **a, t_stack **b, int max_len);
int		op_pa(t_stack **a, t_stack **b, int max_len);
int		op_pb(t_stack **a, t_stack **b, int max_len);
int		op_ra(t_stack **a, t_stack **b, int max_len);
int		op_rb(t_stack **a, t_stack **b, int max_len);
int		op_rr(t_stack **a, t_stack **b, int max_len);
int		op_rra(t_stack **a, t_stack **b, int max_len);
int		op_rrb(t_stack **a, t_stack **b, int max_len);
int		op_rrr(t_stack **a, t_stack **b, int max_len);
void	ft_sort_stacks(t_stack **a, t_stack **b, int max_len, int n);
int		is_stack_sorted(t_stack **a, int n);
void	more_complex_algorithm(t_stack **a, t_stack **b, int max_len, int n);

#endif
