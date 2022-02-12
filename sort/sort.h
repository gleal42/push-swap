/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:09:54 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 23:45:31 by gleal            ###   ########.fr       */
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

void	pb_adjust_max_a(t_elem *b, t_limits *lims_a, t_limits *lims_b);
void	pb_adjust_min_a(t_elem *b, t_limits *lims_a, t_limits *lims_b);
void	pa_adjust_max_b(t_elem *a, t_all *temp);
void	pa_adjust_min_b(t_elem *a, t_all *temp);

// predict_limits_max_min.c

void	pa_predict_adjust_max_a(t_elem *a, t_elem *cur_b, t_limits *lims);
void	pa_predict_adjust_min_a(t_elem *a, t_elem *b, t_limits *lims);
void	pa_predict_adjust_max_b(t_elem *a, t_elem *b, t_limits *lims);
void	pa_predict_adjust_min_b(t_elem *a, t_elem *b, t_limits *lims);

// predict_ramps.c

int		predict_rotationsb_curnbr(t_cmds *temp_cmd,
			t_elem *a, t_elem *b, t_elem *first_nbr,
			t_elem *cur_stack, t_elem **cur_b, t_all *temp, t_limits *limits);
void	predict_place_in_b(t_cmds *cmds, t_elem *b,
			t_elem *tobemoved, t_elem **cur_b, t_all *temp);
int		predict_merge_moves(t_all *all, t_all *temp, t_elem *firstinramp);

//int		predict_merge_moves(t_elem *first_nbr,
//			t_elem *firstinramp, t_elem *a, t_elem *b,
//			t_cmds *temp_cmd, t_all *temp);

// prepare_moves.c

void	merge_ramp_spot(t_all *all, t_all *temp, t_elem *firstinramp);
void	place_in_b(t_elem *b, t_all *temp,
			t_elem *tobemoved);
void	swap_a(t_all *temp, t_elem *tobemoved, t_elem *b);
void	min_push_b_to_a_moves(t_elem *a, t_elem *b, t_all *off);

// sort_algorithm.c

void	ft_sort_stacks(t_all *all, int n);
void	rotate_until_sorted(t_all *all);
int		simple_rotate_algorithm(t_all *all, int n);
void	more_complex_algorithm(t_all *all, int n);
void	sort_a_b(t_all *all, t_all *temp);

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