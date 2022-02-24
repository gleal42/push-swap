/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:13:17 by gleal             #+#    #+#             */
/*   Updated: 2022/02/23 23:28:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "push_swap.h"

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

// stack_utils.c

void	init_stacks_iteration(t_stack *tobeinit, t_elem *ref);
void	iterate_fwd_rev_toend(t_stack *to_iter);
void	iterate_fwd_rev_noend(t_stack *to_iter, t_elem *stack_head);
void	iterate_stack(t_elem **to_iter, t_elem *stack_head);

// other_utils.c

void	delete_stack(int *content);

// predict_rots1.c

void	pred_ramp_rots(t_all *pred, t_all *all,
			t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *));
int		pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd);
void	pred_start_rbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	pred_start_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
void	update_pred_lims_b(t_all *all, t_lims *lims_b, t_elem *check);

// predict_rots2.c

void	pred_all_inirotsb(t_all *all, t_all *pred, t_cmds *rot_pred);
void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred);

// prepare_moves_utils.c

void	ramp_start_before(t_cmds *cmds);
void	init_push_b(t_cmds *cmds);
int		is_good_to_place_wo_rot_b(t_elem *b, t_elem *tobemoved, t_lims lims);
void	add_double_rots_a(t_cmds *cmds);
void	check_if_found_rot(t_elem *move, t_stack *stack,
			t_rot *near_rot, t_lims lims);

// prepare_moves_utils2.c

void	calculate_initial_pushmoves(int closer_fwd,
			int closer_bwd, t_cmds *cmds);
void	find_closest_b_spot(t_elem *cur_b, t_elem *a, t_all *temp, int max);

// sort_algorithm_utils.c

void	rotate_until_sorted(t_all *all);
void	find_rotation_direction(t_all *all, int *rotation_direction);
void	analyze_fwd(t_all **all);
void	analyze_bwd(t_all **all);

#endif
