/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:38:46 by gleal             #+#    #+#             */
/*   Updated: 2021/07/04 16:36:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"

void	print_single_stack(t_stack *stack)
{
	while (stack)
	{
		printf("%d\n", stack->nbr);
		stack = stack->next;
	}
}

void	print_char(char *str, int start, int len)
{
	while (++start <= len)
		printf("%s", str);
}

/* int counter = 0;
	counter++;
	printf("%d\n", counter);
	return ; */

void	print_both_stacks(t_stack *a, t_stack *b)
{
	int	i;
	int	prt;

	return ;
	print_char("_", 0, max_len);
	print_char("_", 1, max_len);
	printf("__");
	printf("\n");
	i = 0;
	while (a || b)
	{
		if (i++ == 0)
		{
			printf(BACKG_B_BLUE);
			printf("A");
			print_char(" ", 0, max_len);
			printf("B");
			print_char(" ", 1, max_len);
			printf(RESET);
			printf("\n");
		}
		prt = 0;
		if (a)
		{
			printf(GRN);
			prt = printf("%d", a->nbr);
			printf(RESET);
			a = a->next;
		}
		print_char(" ", prt, max_len + 1);
		if (b)
		{
			printf(BLU);
			printf("%d", b->nbr);
			printf(RESET);
			b = b->next;
		}
		printf("\n");
	}
}
