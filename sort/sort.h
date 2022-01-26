#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

# define RA 1
# define RRA 2

// execute_moves.c

void	execute_pb_backward(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len);
void	execute_pb_forward(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len);
void	execute_swap_forward(t_cmds *cmds, t_stack **a, t_stack **b, int max_len);
void	execute_swap_backward(t_cmds *cmds, t_stack **a, t_stack **b, int max_len);
void	execute_moves(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len);
void	execute_merge_ab(t_cmds *cmds, t_stack **a, t_stack **b, t_limits *lims, int max_len);

// limits_max_min.c

void	pa_adjust_max_a(t_stack *b, t_limits *lims);
void	pa_adjust_min_a(t_stack *b, t_limits *lims);
void	pa_adjust_max_b(t_stack *a, t_limits *lims);
void	pa_adjust_min_b(t_stack *a, t_limits *lims);

// predict_limits_max_min.c

void	pa_predict_adjust_max_a(t_stack *a, t_stack *cur_b, t_limits *lims);
void	pa_predict_adjust_min_a(t_stack *a, t_stack *b, t_limits *lims);
void	pa_predict_adjust_max_b(t_stack *a, t_stack *b, t_limits *lims);
void	pa_predict_adjust_min_b(t_stack *a, t_stack *b, t_limits *lims);

// predict_ramps.c

int		predict_rotationsb_curnbr(t_cmds *temp_cmd, t_stack *a, t_stack *b, t_stack *first_nbr, t_stack *cur_stack, t_stack **cur_b, t_all *temp, t_limits *limits);
void	predict_place_in_b(t_cmds *cmds, t_stack *b, t_stack *tobemoved, t_stack **cur_b,t_all *temp);
int		predict_merge_moves(t_stack *first_nbr, t_stack *firstinramp, t_stack *a, t_stack *b, t_cmds *temp_cmd, t_all *temp);

// prepare_moves.c

void	merge_ramp_spot(t_stack *a, t_stack *b, t_all *temp, t_stack *firstinramp);
void	place_in_b(t_stack *b, t_all *temp, t_stack *tobemoved);
void	swap_a(t_all *temp, t_stack *tobemoved, t_stack *b);
void	min_push_b_to_a_moves(t_stack *a, t_stack *b, t_all *off);

// sort_algorithm.c

void	rotate_until_sorted(t_stack **a, t_stack **b, int max_len);
void	ft_sort_stacks(t_stack **a, t_stack **b, int max_len, int n);
void	more_complex_algorithm(t_stack **a, t_stack **b, int max_a, int n);

// validations.c

int		is_cmd_table_clean(t_cmds cmds);
int		is_better_ramp(t_cmds temp_cmd, t_cmds off_cmd);
int		continue_ramp_analysis(t_stack *a, t_stack	*first_nbr, t_all *temp);
int		have_analyzed_enough(t_cmds off, t_rot_a ini_rot_a, t_stack *forw_a, t_stack *rev_a);
int		is_temp_better(t_cmds temp, t_cmds off);
int		is_good_for_swap(t_stack *first, t_stack *to_be_swaped, int min_stack, int max_stack);
int		is_next_nbr_bigger(t_stack *cur, t_stack *next_one, int min_stack, int max_stack);
int		is_prev_nbr_smaller(t_stack *cur, t_stack *prev_one, int min_stack, int max_stack);
int		is_stack_sorted(t_stack **a, int n);
int		is_input_integer(char **stack_a_args);

#endif