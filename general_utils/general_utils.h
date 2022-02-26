/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:53:53 by gleal             #+#    #+#             */
/*   Updated: 2022/02/26 22:31:44 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H

# include "push_swap.h"

// get_info.c

int		count_moves(t_cmds *cmds);
int		biggest_str_len(char **strs);
int		nbr_strs(char **strs);

// init_utils.c

void	init_all(t_all *temp, t_all *all, int n);
void	init_rots(t_all *all);
void	init_lims(t_all *all, int n);
void	init_push_b(t_cmds *cmds);

// input_validation.c

int		is_input_integer(char **stack_a_args);

// prepare_moves_utils.c

int		is_good_to_place_wo_rot_b(t_elem *b, t_elem *tobemoved, t_lims lims);
int		is_good_to_place_wo_rot_a(t_elem *a, t_elem *move, t_lims lims_a);
void	check_if_found_rot_a(t_elem *move, t_stack *stack,
			t_rot *near_rot, t_lims lims);
void	check_if_found_rot_b(t_elem *cur_b, t_all *temp);

#endif
