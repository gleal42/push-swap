/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:55:06 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 21:49:14 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "libft.h"
# include "structs.h"
# include "stacks.h"
# include "general_utils.h"

void	checker(char **stack_a_args);
void	add_positions(t_elem	**a, int n);
void	create_cmd_list(const char **all_cmds);
void	ft_execute_checker(t_all *all, int n);
void	validate_input_checker(t_list	*cmd_head);
int		is_cmd(char *str);
void	delete_string(void *str);
void	execute_moves_checker(void);

#endif
