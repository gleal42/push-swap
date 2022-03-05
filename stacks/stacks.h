/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:42:41 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:04:17 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKS_H
# define STACKS_H

# include "push_swap.h"

t_elem		*stacknew(int nbr);
t_elem		*stack_last(t_elem *lst);
void		stack_push_from_to(t_elem **src, t_elem **dst);
void		stack_rotate_forward(t_elem **stack);
void		stack_rotate_backward(t_elem **stack);
t_elem		*stack_second_to_last(t_elem *lst);
int			stacksize(t_elem *stack);
void		stack_swap(t_elem **head);
void		elem_add_back(t_elem **stack, t_elem *new_stack);
void		stacktadd_front(t_elem **stack, t_elem *new_stack);
void		stackdelone(t_elem *stack, void (*del)(int *));
void		stackiter(t_elem *stack, void (*f)(int));
t_elem		*stackmap(t_elem *stack, int (*f)(int), void (*del)(int *));
void		stack_clear(t_elem **stack, void (*del)(int *));

// iterate_utils.c

void		init_stacks_iteration(t_stack *tobeinit, t_elem *ref);
void		iterate_fwd_rev_toend(t_stack *to_iter);
void		iterate_fwd_rev_noend(t_stack *to_iter, t_elem *stack_head);
void		iterate_stack(t_elem **to_iter, t_elem *stack_head);

// other_stack_utils.c

int			is_nbr_in_stack(int nbr, t_elem *a);
void		delete_stack(int *content);

#endif
