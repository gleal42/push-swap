/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:05:41 by gleal             #+#    #+#             */
/*   Updated: 2022/03/03 23:14:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDICT_H
# define PREDICT_H

# include "push_swap.h"

// predict_ramps.c

int		pred_ramp_moves(t_all *all, t_elem *fst);
int		fst_ramp_val(t_elem *head, t_elem *start_secramp, t_lims *lims);
int		scd_ramp_val(t_elem *head, t_elem *start_fstramp, t_lims *lims);
void	pred_ramp_rots(t_all *pred, t_all *all,
			t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *));

// pred_other_rots.c

void	pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd);
void	pred_all_inirotsb(t_all *all, t_all *pred, t_cmds *rot_pred);
void	pred_rots_multi_b(t_all *pred, t_all *all, t_cmds *rot_pred);

// pred_ini_rots.c

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred);

// pred_rots_fwd.c

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
void	add_rbs_find_next(t_all *all, t_all *pred, t_elem **next_fwd);
int		pred_enough_rots_fwd(t_all *pred, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target);
void	update_pred_b_fwd(t_all *pred, t_elem *target);

// pred_rots_bwd.c

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
int		pred_enough_rots_bwd(t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd);
void	add_rrbs_find_prev(t_all *all, t_all *pred, t_elem **prev_bwd);
void	update_pred_b_bwd(t_all *pred, t_elem *target);

// predict_limits.c

void	pred_lims_update(t_elem *first_nbr, t_elem *b, t_all *all, t_all *pred);
void	pred_push_orig_lims(t_elem *fst_ramp, t_elem *ori_head,
			t_stack *cur_ori, t_stack *end);
void	pred_lims_check_pushed(int *has_lim, t_elem *fst_ramp,
			t_elem *ori_head, t_stack *cur_ori);
void	pred_lims_check_end(int *has_lim, t_lims *lims, t_stack *end);
int		did_find_limit(t_elem *anal, t_lims *lims);

#endif
