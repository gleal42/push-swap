/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:09:54 by gleal             #+#    #+#             */
/*   Updated: 2022/02/17 21:48:40 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

# define RA 1
# define RRA 2

// execute_moves.c

void	execute_pb_backward(t_cmds *cmds, t_elem **a,
			t_elem **b, t_all *temp);
void	execute_pb_forward(t_cmds *cmds, t_elem **a,
			t_elem **b, t_all *temp);
void	execute_swap_forward(t_cmds *cmds, t_elem **a,
			t_elem **b);
void	execute_swap_backward(t_cmds *cmds, t_elem **a,
			t_elem **b);
void	execute_moves(t_cmds *cmds, t_stack *a, t_stack *b, t_all *temp);
void	execute_merge_ab(t_cmds *cmds, t_elem **a,
			t_elem **b, t_all *temp);

// limits_max_min.c

void	pb_adjust_max_a(t_elem *b, t_lims *lims_a, t_lims *lims_b);
void	pb_adjust_min_a(t_elem *b, t_lims *lims_a, t_lims *lims_b);
void	pa_adjust_max_b(t_elem *a, t_all *temp);
void	pa_adjust_min_b(t_elem *a, t_all *temp);

// predict_limits.c


void	pred_lims_update(t_elem *first_nbr, t_elem *b, t_all *all, t_all *pred);
void	pred_push_orig_lims(t_elem *fst_ramp, t_elem *ori_head, t_stack *cur_ori, t_stack *end);
void	pred_lims_check_pushed(int *has_lim, t_elem *fst_ramp, t_elem *ori_head, t_stack *cur_ori);
void	pred_lims_check_end(int *has_lim, t_lims *lims, t_stack *end);
int		did_find_limit(t_elem *anal, t_lims *lims);


// predict_ramps.c

int		pred_ramp_moves(t_all *all, t_elem *fst);
void	pred_ramp_rots(t_all *pred, t_all *all, t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *));
int		fst_ramp_val(t_elem *head, t_elem *start_secramp, t_lims *lims);
int		scd_ramp_val(t_elem *head, t_elem *start_fstramp, t_lims *lims);

//int		pred_ramp_moves(t_elem *first_nbr,
//			t_elem *firstinramp, t_elem *a, t_elem *b,
//			t_cmds *temp_cmd, t_all *temp);

// prepare_moves.c

void	merge_ramp_spot(t_all *all, t_elem *firstinramp);
void	place_in_b(t_elem *b, t_all *all, t_elem *tobemoved, t_cmds *cmds);
void	swap_a(t_all *all, t_elem *a);
void	min_push_b_to_a_moves(t_elem *a, t_elem *b, t_all *off);

// sort_algorithm.c

void	ft_sort_stacks(t_all *all, int n);
int		simple_rotate_algorithm(t_all *all, int n);
void	more_complex_algorithm(t_all *all, int n);
void	sort_a_b(t_all *all);
void	merge_a_b(t_all **all);

// validations.c

int		is_cmd_table_clean(t_cmds cmds);
int		is_better_ramp(t_cmds temp_cmd, t_cmds off_cmd);
int		continue_ramp_analysis(t_elem *a, t_elem	*first_nbr, t_all *temp);
int		have_analyzed_enough(t_cmds off, t_rot ini_rot_a,
			t_elem *forw_a, t_elem *rev_a);
int		is_temp_better(t_cmds temp, t_cmds off);
int		is_good_for_swap(t_elem *first, t_elem *to_be_swaped,
			int min_stack, int max_stack);
int		is_next_nbr_bigger(t_elem *cur, t_elem *next_one,
			int min_stack, int max_stack);
int		is_prev_nbr_smaller(t_elem *cur, t_elem *prev_one,
			int min_stack, int max_stack);
int		is_stack_sorted(t_elem **a, int n);

#endif