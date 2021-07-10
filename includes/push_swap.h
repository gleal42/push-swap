#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int			nbr;
	int			pos;
	struct s_stack	*prev;
	struct s_stack	*next;
}				t_stack;

# include "stacks.h"
# include "push_swap_utils.h"
# include "sort_operations.h"

#endif
