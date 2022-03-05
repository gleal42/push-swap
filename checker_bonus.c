/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:26:04 by gleal             #+#    #+#             */
/*   Updated: 2022/03/05 17:56:46 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	main(int argc, char **argv)
{
	if (argc >= 1)
		checker(&argv[1]);
}

/*
** Validates input, creates a stack and sorts it using algorithm
** @param:	- [char **] numbers to be sorted
**
** Line-by-line comments:
** @8	validation to see if all inputs are valid numbers
** @10	Validates duplicate numbers
** 		duplicate validation done inside
** @12	Might be useful to improve algorithm (sort/parameters.c)
*/

void	checker(char **stack_a_args)
{
	t_all	all;
	int		n;

	all.a.head = NULL;
	all.b.head = NULL;
	if (!is_input_integer(stack_a_args))
		return ;
	prepare_stack_a(&(all.a.head), stack_a_args);
	n = nbr_strs(stack_a_args);
	add_positions(&(all.a.head), n);
	check(&all, n);
	stack_clear(&(all.a.head), delete_stack);
	stack_clear(&(all.b.head), delete_stack);
	exit(EXIT_SUCCESS);
}

void	check(t_all *all, int n)
{
	t_list	*cmd_head;
	t_list	*cmd_other;
	char	*str;

	init_check_vars(&cmd_head, &cmd_other, &str);
	while (get_next_line(0, &str))
	{
		if (!is_cmd(str))
		{
			write(2, "Error\n", 6);
			free_checker_memory(&str, &cmd_head);
			return ;
		}
		if (cmd_head == NULL)
			cmd_head = ft_lstnew(str);
		else
		{
			cmd_other = ft_lstnew(str);
			ft_lstadd_back(&cmd_head, cmd_other);
		}
	}
	checker_exec_all_moves(all, cmd_head);
	sorted_checker(all->a.head, all->b.head, n);
	ft_lstclear(&cmd_head, &delete_string);
}

void	checker_exec_all_moves(t_all *all, t_list *cmd_head)
{
	t_list	*temp;

	temp = cmd_head;
	while (temp)
	{
		checker_exec_move(all, temp->content);
		temp = temp->next;
	}
}

void	sorted_checker(t_elem *a, t_elem *b, int max)
{
	t_elem	*a_temp;
	int		i;

	i = 0;
	a_temp = a;
	if (b)
	{
		write(1, "KO\n", 3);
		return ;
	}
	while (a_temp)
	{
		if (++i != a_temp->pos)
		{
			write(1, "KO\n", 3);
			return ;
		}
		a_temp = a_temp->next;
	}
	if (i == max)
		write(1, "OK\n", 3);
}
