/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_validations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:54:02 by gleal             #+#    #+#             */
/*   Updated: 2022/02/18 17:01:56 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

int	is_cmd_table_clean(t_cmds cmds)
{
	if (cmds.sa <= 0
		&& cmds.sb <= 0
		&& cmds.ss <= 0
		&& cmds.ra <= 0
		&& cmds.rb <= 0
		&& cmds.rr <= 0
		&& cmds.pa <= 0
		&& cmds.pb <= 0
		&& cmds.rra <= 0
		&& cmds.rrr <= 0
		&& cmds.rrb <= 0)
		return (1);
	else
		return (0);
}

/*
** Checks if both numbers are good for swapping
** If stack 1 3 2 4
**
** @param:	- [element of stack] element on top of stack (e.g. 1)
**			- [element of stack] element that will be swapped forwards (e.g. 3)
**
** @return:	[int] 1 if it is good for swap
** Line-by-line comments:
** @4	we don't need to swap if the stack has less than 2 members 
** 		(also we prevent a loop (line 9 and 13 combined can't happen)
** @8	if we are comparing the last number of stack with first (2 4 1 3)
** @12	if we are comparing the second to last number with last (4 1 3 2)
*/

int	is_good_for_swap(t_elem *stack_top, t_elem *to_swap,
		int min, int max)
{
	t_elem	*sec;
	t_elem	*frth;

	if (!stack_top || !stack_top->next)
		return (0);
	if (to_swap->next)
		sec = to_swap->next;
	else
		sec = stack_top;
	if (sec->next)
		frth = sec->next;
	else
		frth = stack_top;
	if (is_smaller_than(to_swap->prev, sec, min, max)
		&& is_smaller_than(to_swap, frth, min, max))
		return (1);
	else
		return (0);
}

int	is_smaller_than(t_elem *cur, t_elem *other,
		int min_stack, int max_stack)
{
	if (!other)
		return (1);
	if (cur->pos <= min_stack && other->pos >= max_stack)
		return (0);
	if (other->pos > cur->pos)
		return (1);
	if (cur->pos >= max_stack && other->pos <= min_stack)
		return (1);
	return (0);
}

int	is_bigger_than(t_elem *cur, t_elem *other,
		int min_stack, int max_stack)
{
	if (!other)
		return (1);
	if (cur->pos >= max_stack && other->pos <= min_stack)
		return (0);
	if (other->pos < cur->pos)
		return (1);
	if (cur->pos <= min_stack && other->pos >= max_stack)
		return (1);
	return (0);
}

int	is_stack_sorted(t_elem **a, int n)
{
	t_elem	*temp;

	if (!(*a)->next || !(*a)->next->next)
		return (1);
	temp = *a;
	while (temp->next)
	{
		if (!is_smaller_than(temp, temp->next, 1, n))
			return (0);
		temp = temp->next;
	}
	if (!is_smaller_than(temp, *a, 1, n))
		return (0);
	else
		return (1);
}
