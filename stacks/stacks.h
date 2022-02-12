/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:42:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:16:39 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "push_swap.h"

t_elem		*stacknew(int nbr);

t_elem		*stack_last(t_elem *lst);

void		elem_add_back(t_elem **stack, t_elem *new_stack);
void		stacktadd_front(t_elem **stack, t_elem *new_stack);
int			stacksize(t_elem *stack);
t_elem		*stack_second_to_last(t_elem *lst);
void		stack_swap(t_elem **head);
int			is_nbr_in_stack(int nbr, t_elem *a);
void		stackdelone(t_elem *stack, void (*del)(int *));
void		stackiter(t_elem *stack, void (*f)(int));
void		stack_swap(t_elem **head);

t_elem		*stackmap(t_elem *stack, int (*f)(int), void (*del)(int *));

void		stack_clear(t_elem **stack, void (*del)(int *));

void		stack_push_from_to(t_elem **src, t_elem **dst);
void		stack_rotate_forward(t_elem **stack);
void		stack_rotate_backward(t_elem **stack);

void		print_single_stack(t_elem *stack);
void		print_both_stacks(t_elem *a, t_elem *b);
#endif
