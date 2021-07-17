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

typedef struct s_ini_rot_a
{
	int			ra;
	int			rra;
}				t_ini_rot_a;

typedef struct s_ini_rot_b
{
	int			rb;
	int			rrb;
}				t_ini_rot_b;

typedef struct s_cmd_list
{
	t_stack 		*norm_a;
	t_stack 		*rev_a;
	t_stack 		*norm_b;
	t_stack 		*rev_b;
	t_ini_rot_a		ini_rot_a;;
	t_ini_rot_b		ini_rot_b;;
	int				sa;
	int				sb;
	int				ss;
	int				ra;
	int				rb;
	int				rr;
	int				pa;
	int				pb;
	int				rra;
	int				rrb;
	int				rrr;
}				t_cmd_list;

# include "stacks.h"
# include "push_swap_utils.h"
# include "sort_operations.h"

#endif
