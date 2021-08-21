/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:11:18 by gleal             #+#    #+#             */
/*   Updated: 2021/08/21 23:17:17 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap_utils.h"
// min_a and max_a have to be found by analyzing stack b and checking for the position has to be updated to reflect the highest number in stack a

int	is_good_position_forward(t_stack *cur, t_stack *next_one, int min_a, int max_a)
{
	if (!next_one)
		return (1);
	if(next_one->nbr > cur->nbr || (cur->pos == max_a && next_one->pos == min_a))
		return (1);
	else
		return (0);
}

int	is_good_position_backward(t_stack *cur, t_stack *prev_one, int min_a, int max_a)
{
	if (!prev_one)
		return (1);
	if (prev_one->nbr < cur->nbr || (cur->pos == min_a && prev_one->pos == max_a))
		return (1);
	else
		return (0);
}

void	init_rot_b(t_all *all)
{
	all->ini_rot_b.rb = 0;
	all->ini_rot_b.rrb = 0;
}

void	init_rot_a(t_all *all)
{
	all->ini_rot_a.ra = 0;
	all->ini_rot_a.rra = 0;
}

void	init_cmd_list(t_cmds *cmds)
{
	cmds->sa = 0;
	cmds->sb = 0;
	cmds->ss = 0;
	cmds->ra = 0;
	cmds->rb = 0;
	cmds->rr = 0;
	cmds->pa = 0;
	cmds->pb = 0;
	cmds->rra = 0;
	cmds->rrr = 0;
	cmds->rrb = 0;
	cmds->total = 0;
	cmds->type = 0;
}

int	is_input_integer(char **stack_a_args)
{
	int i;

	i = 0;
	if (!stack_a_args[0])
		return (0);
	while (stack_a_args[i])
	{
		if (!is_integer(stack_a_args[i]))
		{

			printf("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
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

void calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds)
{
	int fwd_total;
	int rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (has_rb)
		fwd_total = cmds->ra + cmds->rb +cmds->rr + cmds->pa;
	if (has_rrb)
		rev_total = cmds->rra + cmds->rrb + cmds->rrr + cmds->pa;
	if ((fwd_total < rev_total && has_rb)|| !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((fwd_total < rev_total && has_rb) || !has_rrb)
	{
		cmds->rb = 0;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
}