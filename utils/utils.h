/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:13:17 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 20:49:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "push_swap.h"

// execute_moves_utils.c

void	set_lims_stack_a_pb(t_stack **a, t_stack **b, t_limits *lims);
void	set_both_a_lims_as(t_limits *lims, int value);
void	set_lims_stack_b_pb(t_stack **a, t_stack **b, t_limits *lims);
void	set_both_b_lims_as(t_limits *lims, int value);

// execute_moves_utils2.c

void	set_lims_stack_b_pa(t_stack **a, t_stack **b, t_limits *lims);
void	set_lims_stack_a_pa(t_stack **a, t_stack **b, t_limits *lims);

// get_info.c

int		count_moves(t_cmds *cmds);
int		biggest_str_len(char **strs);
int		nbr_strs(char **strs);

// init_utils.c

void	init_temp_all(t_all *temp, t_all *all, int n);
void	init_rots(t_all *all);
void	init_lims(t_all *all, int n);

// init_utils2.c

void	init_stacks_iteration_a(t_all *tobeinit, t_all *ref);

// other_utils.c

void	delete_stack(int *content);

// predict_ramps_utils.c

void	predict_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);

// prepare_moves_utils.c

void	not_rotate_fwd(t_cmds *cmds);
void	init_push_b(t_all *temp);
int	is_good_to_place_no_rot_b(t_stack *b, t_stack *tobemoved, t_limits lims);
void	add_double_rots_a(t_cmds *cmds);
void	check_if_found_rot(t_all *temp, t_stack *tobemoved, int *fwd, int *bwd);

// prepare_moves_utils2.c

void	calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);
void	find_closest_b_spot(t_stack *cur_b, t_stack *a, t_all *temp, int max);

// sort_algorithm_utils.c

void	rotate_until_sorted(t_all *all);
void	sort_a_b(t_all *all, t_all *temp);
void	merge_a_b(t_all **all, t_all *temp);

// sort_algorithm_utils2.c

void	find_rotation_direction(t_all *all, int *rotation_direction);
void	analyze_fwd(t_all **all, t_all *temp);
void	analyze_bwd(t_all **all, t_all *temp);

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
