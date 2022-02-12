/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:47:22 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:01:30 by gleal            ###   ########.fr       */
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
# include "utils.h"
# include "sort.h"
# include "validations.h"

void				push_swap(char **stack_a_args);
void				prepare_stack_a(t_elem **a, char **stack_a_args);
void				add_positions(t_elem	**a, int n);

#endif