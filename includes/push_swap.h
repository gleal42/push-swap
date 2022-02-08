#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "structs.h"
# include "colours.h"
# include "malloc_leak_checker.h"
# include "stacks.h"
# include "operations.h"
# include "utils.h"
# include "sort.h"
# include "validations.h"

void				push_swap(char **stack_a_args);
void				prepare_stack_a(t_stack **a, char **stack_a_args);
void				add_positions(t_stack	**a, int n);

#endif