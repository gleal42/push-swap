/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:19:57 by gleal             #+#    #+#             */
/*   Updated: 2022/02/10 14:59:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_stacks_iteration(t_all *tobeinit, t_all *ref)
{
	tobeinit->forw_a = ref->a;
	tobeinit->rev_a = ref->a;
}