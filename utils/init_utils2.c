/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:19:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 19:29:57 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_stacks_iteration_a(t_all *tobeinit, t_all *ref)
{
	tobeinit->forw_a = ref->a;
	tobeinit->rev_a = ref->a;
}

void	init_stacks_iteration_b(t_all *tobeinit, t_all *ref)
{
	tobeinit->forw_b = ref->b;
	tobeinit->rev_b = ref->b;
}
