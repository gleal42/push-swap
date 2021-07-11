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

typedef struct s_cmd_list
{
	int			sa;
	int			sb;
	int			ss;
	int			ra;
	int			rb;
	int			rr;
	int			pa;
	int			pb;
	int			rra;
	int			rrb;
	int			rrr;
}				t_cmd_list;

# include "stacks.h"
# include "push_swap_utils.h"
# include "sort_operations.h"

#endif
