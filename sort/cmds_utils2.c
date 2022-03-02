/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:16:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/02 02:20:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

void	update_exec_cmds(t_all **all)
{
	if (is_temp_better(*all))
	{
		(*all)->exec_cmds = (*all)->pred_cmds;
		(*all)->ramp_cmds = (*all)->a.ramp.best_cmds;
	}
}
