/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:16:45 by gleal             #+#    #+#             */
/*   Updated: 2022/01/25 22:17:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

int	count_moves(t_cmds *cmds)
{
	int total;

	total = 0;
	total += cmds->sa;
	total += cmds->sb;
	total += cmds->ss;
	total += cmds->ra;
	total += cmds->rb;
	total += cmds->rr;
	total += cmds->pa;
	total += cmds->pb;
	total += cmds->rra;
	total += cmds->rrb;
	total += cmds->rrr;
	return (total);
}

int	biggest_str_len(char **strs)
{
	int i;
	int len;
	int temp;

	i = 0;
	len = 0;
	if (!strs)
		return 0;
	while (strs[i])
	{
		temp = ft_strlen(strs[i]);
		if (temp > len)
			len = temp;
		i++;
	}
	return (len);
}