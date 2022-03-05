/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:33:56 by gleal             #+#    #+#             */
/*   Updated: 2022/03/05 17:02:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	init_check_vars(t_list **cmd_head, t_list **cmd_other, char **str)
{
	*str = 0;
	*cmd_head = NULL;
	*cmd_other = NULL;
}

int	is_cmd(char *str)
{
	const char	*all_cmds[12];
	int			i;

	create_cmd_list(all_cmds);
	i = 0;
	while (all_cmds[i])
	{
		if (!ft_strncmp(str, all_cmds[i], ft_strlen(all_cmds[i]))
			&& ft_strlen(str) == ft_strlen(all_cmds[i]))
			return (1);
		i++;
	}	
	return (0);
}

void	checker_exec_move(t_all *all, char *str)
{
	if (!ft_strncmp(str, "ra", ft_strlen("ra")))
		stack_rotate_backward(&all->a.head);
	else if (!ft_strncmp(str, "rra", ft_strlen("rra")))
		stack_rotate_forward(&all->a.head);
	else if (!ft_strncmp(str, "pb", ft_strlen("pb")))
		stack_push_from_to(&all->a.head, &all->b.head);
	else if (!ft_strncmp(str, "rb", ft_strlen("rb")))
		stack_rotate_backward(&all->b.head);
	else if (!ft_strncmp(str, "rrb", ft_strlen("rrb")))
		stack_rotate_forward(&all->b.head);
	else if (!ft_strncmp(str, "rr", ft_strlen("rr")))
		rot_back_both_stacks(&all->a.head, &all->b.head);
	else if (!ft_strncmp(str, "rrr", ft_strlen("rrr")))
		rot_fwd_both_stacks(&all->a.head, &all->b.head);
	else if (!ft_strncmp(str, "pa", ft_strlen("pa")))
		stack_push_from_to(&all->b.head, &all->a.head);
	else if (!ft_strncmp(str, "sa", ft_strlen("sa")))
		stack_swap(&all->a.head);
	else if (!ft_strncmp(str, "sb", ft_strlen("sb")))
		stack_swap(&all->b.head);
	else if (!ft_strncmp(str, "ss", ft_strlen("ss")))
		swap_both_stacks(&all->a.head, &all->b.head);
}
