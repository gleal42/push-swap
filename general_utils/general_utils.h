/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:53:53 by gleal             #+#    #+#             */
/*   Updated: 2022/03/01 23:16:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H

# include "push_swap.h"

// input.c

int		count_moves(t_cmds *cmds);
int		is_input_integer(char **stack_a_args);
int		biggest_str_len(char **strs);
int		nbr_strs(char **strs);

// init_utils.c

void	init_all(t_all *temp, t_all *all, int n);
void	init_rots(t_all *all);
void	init_lims(t_all *all, int n);
void	init_push_b(t_cmds *cmds);

// good_push_validations.c

int		is_good_to_place_wo_rot_b(t_elem *b, t_elem *tobemoved, t_lims lims);
int		is_good_to_place_wo_rot_a(t_elem *a, t_elem *move, t_lims lims_a);
void	check_if_found_rot_a(t_elem *move, t_stack *stack,
			t_rot *near_rot, t_lims lims);
void	check_if_found_rot_b(t_elem *cur_b, t_all *temp);
int		is_inbetween_bigger(t_elem *fst, t_elem *sec,
			t_elem *thrd, t_lims lims);

// other_cmds_utils.c

void	add_update_cmd(int *toupdate, t_cmds *cmds, int value);
void	subt_update_cmd(int *toupdate, t_cmds *cmds, int value);

#endif
