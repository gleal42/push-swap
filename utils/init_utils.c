/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:45:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/10 17:33:14 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_temp_all(t_all *temp, t_all *all, int n)
{
	init_rots(all);
	init_lims(all, n);
	ft_bzero(&all->exec_cmds, sizeof(t_cmds));
	ft_bzero(&all->pred_cmds, sizeof(t_cmds));
	init_stacks_iteration_a(all, all);
	*temp = *all;
}

void	init_rots(t_all *all)
{
	ft_bzero(&all->ini_rot_a, sizeof(t_rot_a));
	ft_bzero(&all->ini_rot_b, sizeof(t_rot_b));
}

void	init_lims(t_all *all, int n)
{
	all->lims.min_a = 1;
	all->lims.max_a = n;
	all->lims.min_b = 0;
	all->lims.max_b = 0;
}
