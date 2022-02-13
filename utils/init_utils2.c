/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:19:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/13 16:46:03 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_stacks_iteration(t_stack *tobeinit, t_elem *ref)
{
	tobeinit->forw = ref;
	tobeinit->rev = ref;
}
