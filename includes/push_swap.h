#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H


typedef struct s_stack
{
	int			nbr;
	int			pos;
	struct s_stack	*prev;
	struct s_stack	*next;
}				t_stack;

typedef struct s_rot_a
{
	int			ra;
	int			rra;
}				t_rot_a;

typedef struct s_rot_b
{
	int			rb;
	int			rrb;
}				t_rot_b;

typedef struct s_limits
{
	int			min_a;
	int			max_a;
	int			min_b;
	int			max_b;
}				t_limits;

typedef struct s_cmds
{
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
	int				total;
	int				type;
}				t_cmds;

typedef struct s_all
{
	t_stack 		*forw_a;
	t_stack 		*rev_a;
	t_stack 		*forw_b;
	t_stack 		*rev_b;
	t_rot_a			ini_rot_a;;
	t_rot_b			ini_rot_b;;
	t_cmds			cmds;
	t_limits		lims;
}				t_all;

enum	e_moves
{
	PUSH_B_FWD,
	PUSH_B_BWD,
	SWAP_FWD,
	SWAP_BWD,
	PUSH_BACK
};

# include "libft.h"
# include "stacks.h"
# include "operations.h"
# include "utils.h"
# include "sort.h"

#endif
