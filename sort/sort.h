/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:09:54 by gleal             #+#    #+#             */
/*   Updated: 2022/03/02 22:08:44 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

# define RA 1
# define RRA 2

// cmds_utils.c

void	add_double_rots_a(t_cmds *cmds);
void	add_double_rots_b(t_cmds *cmds, int	*fwd_total, int *rev_total);
void	calculate_initial_pb_moves(int best_fwd, int best_bwd, t_cmds *cmds);
void	calculate_initial_pa_moves(int best_fwd, int best_bwd, t_cmds *cmds);
void	ramp_start_before(t_cmds *cmds);

// cmds_utils2.c

void	update_exec_cmds(t_all **all);

// limits.c

void	set_lims_ori_push(t_stack *a, t_stack *b);
void	set_lims_other_push(t_stack *ori, t_stack *other);
void	set_both_lims_as(t_lims *lims, int value);
void	adj_lims_ori_push(t_stack *origin, t_stack *other);

// sort_a_b_utils.c

void	analyze_fwd(t_all **all);
void	analyze_bwd(t_all **all);

// sort_a_b.c

void	merge_ramp_spot(t_all *all, t_elem *firstinramp);
void	place_in_b_rots(t_elem *b, t_all *all, t_elem *tobemoved, t_cmds *cmds);
void	swap_a(t_all *all, t_elem *a);

// merge_a_b.c

void	place_in_a(t_all *all);
void	place_in_a_fwd(t_all *all, t_all *temp);
void	place_in_a_bwd(t_all *all, t_all *temp);
void	find_spot_for_cur_b(t_elem *cur_b, t_all *temp, int max);
void	init_find_closest_b_spot(t_all *temp);

// sort_algorithm.c

void	ft_sort_stacks(t_all *all, int n);
int		simple_rotate_algorithm(t_all *all, int n);
void	more_complex_algorithm(t_all *all, int n);
void	sort_a_b(t_all *all);
void	merge_a_b(t_all **all);

// sort_validations.c

int		is_cmd_table_clean(t_cmds cmds);
int		is_good_for_swap(t_elem *first, t_elem *to_be_swaped,
			int min_stack, int max_stack);
int		is_smaller_than(t_elem *cur, t_elem *next_one,
			int min_stack, int max_stack);
int		is_bigger_than(t_elem *cur, t_elem *prev_one,
			int min_stack, int max_stack);
int		is_stack_sorted(t_elem **a, int n);

// sort_parameters.c

int		is_better_ramp(t_cmds temp_cmd, t_cmds off_cmd);
int		have_analyzed_enough(t_all *all);
int		all_number_checked(t_all *all);
int		is_temp_better(t_all *all);
int		stop_pred_ramps(t_all *all, t_elem *firstinramp);

#endif