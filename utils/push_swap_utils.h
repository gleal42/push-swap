#ifndef PUSH_SWAP_UTILS_H
# define PUSH_SWAP_UTILS_H

# include "push_swap.h"

int	is_input_integer(char **stack_a_args);
int	biggest_str_len(char **strs);
void	init_cmd_list(t_cmds *cmds);
void	init_rot_b(t_all *cmds);
int	is_next_nbr_bigger(t_stack *cur, t_stack *next_one, int min_a, int max_a);
int	is_prev_nbr_smaller(t_stack *cur, t_stack *prev_one, int min_a, int max_a);
void calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);
int		is_good_for_swap(t_stack *first, t_stack *to_be_swaped, int min_stack, int max_stack);
int	count_moves(t_cmds *cmds);
int is_temp_better(t_cmds temp, t_cmds off);
int	have_analyzed_enough(t_cmds off, t_rot_a ini_rot_a, t_stack *forw_a, t_stack *rev_a);
int	continue_ramp_analysis(t_stack *a, t_stack	*first_nbr, t_all *temp);
int	predict_merge_moves(t_stack *first_nbr, t_stack *last_nbr, t_stack *a, t_stack *b, t_cmds *temp_cmd, t_all *temp);

#endif
