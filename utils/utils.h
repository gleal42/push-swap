/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:13:17 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 19:27:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "push_swap.h"

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

// prepare_moves_utils.c

void	not_rotate_fwd(t_cmds *cmds);
void	find_closest_b_spot(t_stack *cur_b, t_stack *a, t_all *temp, int max);
void	predict_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);
void	calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);

// sort_algorithm_utils.c

void	rotate_until_sorted(t_all *all, int max_len);
void	sort_a_b(t_all *all, t_all *temp, int max_a);
void	merge_a_b(t_all **all, t_all *temp, int max_a);

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
