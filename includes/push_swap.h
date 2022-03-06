/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:47:22 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 16:10:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

int		max_len;
# include "libft.h"
# include "structs.h"
# include "colours.h"
# include "malloc_leak_checker.h"
# include "stacks.h"
# include "operations.h"
# include "sort.h"
# include "predict.h"
# include "execute.h"
# include "general_utils.h"

void			push_swap(char **stack_a_args);
int				prepare_stack_a(t_elem **a, char **stack_a_args);
void			add_positions(t_elem	**a, int n);

#endif