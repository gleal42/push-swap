/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:42:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/11 19:43:01 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "push_swap.h"

t_stack		*stacknew(int nbr);

t_stack		*stack_last(t_stack *lst);

void		stackadd_back(t_stack **stack, t_stack *new_stack);
void		stacktadd_front(t_stack **stack, t_stack *new_stack);
int			stacksize(t_stack *stack);
t_stack		*stack_second_to_last(t_stack *lst);
void		stack_swap(t_stack **head);
int			is_nbr_in_stack(int nbr, t_stack *a);
void		stackdelone(t_stack *stack, void (*del)(int *));
void		stackiter(t_stack *stack, void (*f)(int));
void		stack_swap(t_stack **head);

t_stack		*stackmap(t_stack *stack, int (*f)(int), void (*del)(int *));

void		stacks_clear(t_stack **stack, void (*del)(int *));

void		stack_push_from_to(t_stack **src, t_stack **dst);
void		stack_rotate_forward(t_stack **stack);
void		stack_rotate_backward(t_stack **stack);

void		print_single_stack(t_stack *stack);
void		print_both_stacks(t_stack *a, t_stack *b, int max_len);
#endif
