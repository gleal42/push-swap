/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:44:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/02 02:02:29 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	add_update_cmd(int *toupdate, t_cmds *cmds, int value)
{
	*toupdate = *toupdate + value;
	cmds->total = cmds->total + value;
}

void	subt_update_cmd(int *toupdate, t_cmds *cmds, int value)
{
	*toupdate = *toupdate - value;
	cmds->total = cmds->total - value;
}
