/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:05:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:32:27 by gleal            ###   ########.fr       */
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
void	find_next_pred_lower(t_all *all, t_all *pred, t_elem	**check_fwd);
void	update_pred_b_head_fwd(t_all *all, t_all *pred,
			t_elem **target, t_elem	*check_fwd);

// pred_rots_bwd.c

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred);
void	find_next_pred_bigger(t_all *all, t_all *pred, t_elem **check_bwd);
void	update_pred_b_head_bwd(t_all *pred, t_elem **target, t_elem	*check_bwd);

// pred_rots_empty_b.c

void	predict_all_ini_rbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	predict_next_ini_rb_nbr(t_all *pred);
int		update_pred_rbs_reset(t_all *all, t_all *pred, int *rot_pred);

// pred_ini_rots2.c

void	predict_all_ini_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred);
void	predict_next_ini_rrb_nbr(t_all *pred);
int		update_pred_rrbs_reset(t_all *all, t_all *pred, int *rot_pred);

#endif
