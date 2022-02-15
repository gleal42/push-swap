/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 21:45:45 by gleal             #+#    #+#             */
/*   Updated: 2022/02/14 23:55:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_all(t_all *temp, t_all *all, int n)
{
	init_rots(all);
	init_lims(all, n);
	ft_bzero(&all->pred_cmds, sizeof(t_cmds));
	ft_bzero(&all->exec_cmds, sizeof(t_cmds));
	init_stacks_iteration(&all->a, all->a.head);
	*temp = *all;
}

void	init_rots(t_all *all)
{
	ft_bzero(&all->a.ini_rot, sizeof(t_rot));
	ft_bzero(&all->b.ini_rot, sizeof(t_rot));
}

void	init_lims(t_all *all, int n)
{
	all->a.lims.min = 1;
	all->a.lims.max = n;
	all->b.lims.min = 0;
	all->b.lims.max = 0;
}
