/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:26:04 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 21:50:36 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker_bonus.h"

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
	ft_execute_checker(&all, n);
	stack_clear(&(all.a.head), delete_stack);
	stack_clear(&(all.b.head), delete_stack);
	exit(EXIT_SUCCESS);
}

void	add_positions(t_elem	**a, int n)
{
	t_elem		*first;
	t_elem		*next_min;
	int			i;

	i = 1;
	first = (*a);
	while (i <= n)
	{
		*a = first;
		next_min = 0;
		while (*a)
		{
			if (! (*a)->pos
				&& (next_min == 0 || ((*a)->nbr < next_min->nbr)))
				next_min = *a;
			*a = (*a)->next;
		}
		*a = next_min;
		(*a)->pos = i;
		i++;
	}
	*a = first;
}

void	ft_execute_checker(t_all *all, int n)
{
	t_list	*cmd_head;
	t_list	*cmd_other;
	char *str;

	(void)all;
	(void)n;
	str = 0;
	cmd_head = NULL;
	cmd_other = NULL;
	while (get_next_line(0, &str))
	{
		if (!is_cmd(str))
		{
			write(2, "Error\n", 6);
			ft_lstclear(&cmd_head, &delete_string);
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
	execute_moves_checker();
	//sorted_checker();
}

void	execute_moves_checker(void)
{
	write(1, "LETSS GOOO\n", ft_strlen( "LETSS GOOO\n"));
}

void	sorted_checker(void)
{

}

int	is_cmd(char *str)
{
	const char *all_cmds[12];
	int i;

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

void	create_cmd_list(const char **all_cmds)
{
	all_cmds[0] = "sa";
	all_cmds[1] = "sb";
	all_cmds[2] = "ss";
	all_cmds[3] = "ra";
	all_cmds[4] = "rb";
	all_cmds[5] = "rr";
	all_cmds[6] = "pa";
	all_cmds[7] = "pb";
	all_cmds[8] = "rra";
	all_cmds[9] = "rrb";
	all_cmds[10] = "rrr";
	all_cmds[11] = 0;
}

void	delete_string(void *str)
{
	free(str);
	str = NULL;
}
