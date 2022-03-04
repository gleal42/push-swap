/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:44:49 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 17:27:18 by gleal            ###   ########.fr       */
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

t_elem	*next_elem(t_elem *elem, t_elem *head)
{
	if (elem->next)
		return (elem->next);
	else
		return (head);
}

float	pred_formula(t_cmds cmds, t_elem *firstinramp, int n)
{
	(void)firstinramp;
	(void)n;
	return (cmds.total);
}
