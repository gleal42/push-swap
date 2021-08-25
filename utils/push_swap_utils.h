#ifndef PUSH_SWAP_UTILS_H
# define PUSH_SWAP_UTILS_H

# include "push_swap.h"

int	is_input_integer(char **stack_a_args);
int	biggest_str_len(char **strs);
void	init_cmd_list(t_cmds *cmds);
void	init_rot_b(t_all *cmds);
int	is_good_position_forward_same_stack(t_stack *cur, t_stack *next_one, int min_a, int max_a);
int	is_good_position_backward_same_stack(t_stack *cur, t_stack *prev_one, int min_a, int max_a);
void calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);

#endif
