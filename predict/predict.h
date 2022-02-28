/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:05:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/28 17:20:04 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDICT_H
# define PREDICT_H

# include "push_swap.h"

// pred_rots.c

void	pred_ramp_rots(t_all *pred, t_all *all,
			t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *));
void	update_pred_lims_b(t_all *all, t_lims *lims_b, t_elem *check);
void	update_max_min(t_elem	*temp, int *min, int *max);

// pred_other_rots.c

void	pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd);
void	pred_all_inirotsb(t_all *all, t_all *pred, t_cmds *rot_pred);
void	pred_rots_multi_b(t_all *pred, t_all *all, t_cmds *rot_pred);

// pred_rots_fwd.c

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
void	ready_to_place(t_all *pred, t_elem **target, t_elem	*check_fwd);
void	add_rbs_find_next(t_all *all, t_all *pred, t_elem **next_fwd);
int		pred_enough_rots_fwd(t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target);
int		is_inbetween_bigger(t_elem *fst, t_elem *sec, t_elem *thrd, t_lims lims);
void	update_pred_b_fwd(t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target);

// pred_rots_bwd.c

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
void	add_rrbs_find_prev(t_all *all, t_all *pred, t_elem **prev_bwd);
void	update_pred_b_bwd(t_all *all, t_all *pred, t_elem *prev_bwd, t_elem *cur_bwd, t_elem *next_bwd, t_elem *target);
int		pred_enough_rots_bwd(t_all *all, t_all *pred, t_elem *prev_fwd, t_elem *cur_fwd, t_elem *next_fwd, t_elem *target);

// pred_ini_rbs.c

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	ini_rbs_find_next_lower(t_all *all, t_all *pred);
void	ini_update_pred_rbs_elem(t_all *pred, int *rot_pred);

// pred_ini_rrbs.c

void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	ini_rrbs_find_next_bigger(t_all *all, t_all *pred);
void	ini_update_pred_rrbs_elem(t_all *pred, int *rot_pred);

#endif
