#ifndef UTILS_H
# define UTILS_H

# include "push_swap.h"

// get_info.c

int		count_moves(t_cmds *cmds);
int		biggest_str_len(char **strs);
int		nbr_strs(char **strs);

// init_utils.c

void	init_rot_a(t_all *all);
void	init_rot_b(t_all *cmds);
void	init_cmd_list(t_cmds *cmds);
void	init_cmd_list_exc_total(t_cmds *cmds);

// other_utils.c

void	delete_stack(int *content);

// prepare_moves_utils.c

void	find_closest_b_spot(t_stack *cur_b, t_stack *a, t_all *temp, int max);
void	predict_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);
void	calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);

// update_values.c

void	add_rbs(t_stack *a, t_stack *first_nbr,
			t_stack *cur_stack, t_stack *forw_b,
			t_cmds *nbr_rot_pred, t_limits *limits);
void	add_rrbs(t_stack *a, t_stack *first_nbr,
			t_stack *cur_stack, t_stack *rev_b,
			t_cmds *nbr_rot_pred, t_limits *limits);
void	update_cur_b(t_cmds *cmds, t_stack **cur_b_head,
			t_stack *fwd_b, t_stack *bwd_b);
void	add_new_rotatesb(t_stack *b, int has_rb,
			int has_rrb, t_cmds *cmds, t_stack *cur_stack,
			t_stack **cur_b, t_limits *limits);
void	update_predict_limits(t_stack *first_nbr,
			t_stack *cur_a, t_stack *cur_b, t_stack *a,
			t_stack *b, t_all *pred_limits);

#endif
