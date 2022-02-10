/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:13:09 by gleal             #+#    #+#             */
/*   Updated: 2022/02/10 16:13:10 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATIONS_H
# define VALIDATIONS_H

# include "push_swap.h"

int		is_input_integer(char **stack_a_args);
int		is_nbr_in_stack(int nbr, t_stack *a);

#endif