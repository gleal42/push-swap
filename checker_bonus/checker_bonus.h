/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:55:06 by gleal             #+#    #+#             */
/*   Updated: 2022/03/05 17:57:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "libft.h"
# include "structs.h"
# include "stacks.h"
# include "general_utils.h"

//root

void	checker(char **stack_a_args);
void	add_positions(t_elem	**a, int n);
void	create_cmd_list(const char **all_cmds);
void	check(t_all *all, int n);
void	validate_input_checker(t_list	*cmd_head);
int		is_cmd(char *str);
void	delete_string(void *str);
void	checker_exec_all_moves(t_all *all, t_list *cmd_head);
void	sorted_checker(t_elem *a, t_elem *b, int max);
void	checker_exec_move(t_all *all, char *str);
void	rot_back_both_stacks(t_elem **a, t_elem **b);
void	rot_fwd_both_stacks(t_elem **a, t_elem **b);
void	swap_both_stacks(t_elem **a, t_elem **b);
void	init_check_vars(t_list **cmd_head, t_list **cmd_other, char **str);
void	free_checker_memory(char **str, t_list **cmd_head);

#endif
