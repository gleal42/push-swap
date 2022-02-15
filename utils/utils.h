/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:13:17 by gleal             #+#    #+#             */
/*   Updated: 2022/02/15 01:50:47 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "push_swap.h"

// execute_moves_utils.c

void	set_lims_stack_a_pb(t_elem **a, t_elem **b, t_all *temp);
void	set_lims_stack_b_pb(t_elem **a, t_elem **b, t_all *temp);
void	set_both_lims_as(t_lims *lims, int value);

// execute_moves_utils2.c

void	set_lims_stack_b_pa(t_elem **a, t_elem **b, t_all *temp);
void	set_lims_stack_a_pa(t_elem **a, t_elem **b, t_all *temp);

// get_info.c

int		count_moves(t_cmds *cmds);
int		biggest_str_len(char **strs);
int		nbr_strs(char **strs);

// init_utils.c

void	init_all(t_all *temp, t_all *all, int n);
void	init_rots(t_all *all);
void	init_lims(t_all *all, int n);

// init_utils2.c

void	init_stacks_iteration(t_stack *tobeinit, t_elem *ref);

// other_utils.c

void	delete_stack(int *content);

// predict_ramps_utils.c

void	pred_lims_update(t_elem *first_nbr, t_elem *cur_a, t_elem *cur_b, t_elem *b, t_all *pred);
void	pred_ini_rots(t_cmds *cmds, t_elem *b,
		t_elem *tobemoved, t_elem **cur_b, t_all *pred);
int	pred_other_rots(t_cmds *temp_cmd, t_elem *a,
		t_elem *b, t_elem *first_nbr, t_elem *cur_stack,
		t_elem **cur_b, t_all *all, t_lims *lims_b);
void	predict_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);

// prepare_moves_utils.c

void	rotate_bwd(t_cmds *cmds);
void	init_push_b(t_all *temp);
int	is_good_to_place_wo_rot_b(t_elem *b, t_elem *tobemoved, t_lims lims);
void	add_double_rots_a(t_cmds *cmds);
void	check_if_found_rot(t_all *temp, t_elem *tobemoved, int *fwd, int *bwd);

// prepare_moves_utils2.c

void	calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds);
void	find_closest_b_spot(t_elem *cur_b, t_elem *a, t_all *temp, int max);

// sort_algorithm_utils.c

void	rotate_until_sorted(t_all *all);
void	find_rotation_direction(t_all *all, int *rotation_direction);
void	analyze_fwd(t_all **all);
void	analyze_bwd(t_all **all);

// sort_algorithm_utils2.c


// update_values.c

void	add_rbs(t_elem *a, t_elem *first_nbr,
			t_elem *cur_stack, t_elem *forw_b,
			t_cmds *nbr_rot_pred, t_lims *limits);
void	add_rrbs(t_elem *a, t_elem *first_nbr,
			t_elem *cur_stack, t_elem *rev_b,
			t_cmds *nbr_rot_pred, t_lims *limits);
void	update_cur_b(t_cmds *cmds, t_elem **cur_b_head,
			t_elem *fwd_b, t_elem *bwd_b);
void	add_new_rotatesb(int has_rb,
		int has_rrb, t_cmds *cmds);
void	pred_lims_update(t_elem *first_nbr, t_elem *cur_a, t_elem *cur_b, t_elem *b, t_all *pred);

#endif
