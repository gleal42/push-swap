/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:49:21 by gleal             #+#    #+#             */
/*   Updated: 2022/03/03 19:26:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rot
{
	int			r;
	int			rrev;
}				t_rot;

typedef struct s_lims
{
	int			min;
	int			max;
}				t_lims;

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
	int				ramp_size;
}				t_cmds;

typedef struct s_elem
{
	int				nbr;
	int				pos;
	struct s_elem	*prev;
	struct s_elem	*next;
}				t_elem;

typedef struct s_ramp
{
	t_cmds		init_cmds;
	t_cmds		best_cmds;
	t_cmds		init_pb;
	t_cmds		best_pb;
	t_elem		*first_nbr;
	t_elem		*sent;
	t_elem		*off_nbr;
	t_elem		*prev_nbr;
}				t_ramp;

typedef struct s_pred_rots
{
	t_elem	*prev;
	t_elem	*cur;
	t_elem	*next;
	t_elem	*off;
	t_elem	*target;
}				t_pred_rots;

typedef struct s_stack
{
	t_elem		*head;
	t_elem		*forw;
	t_elem		*rev;
	t_rot		ini_rot;
	t_rot		near_rot;
	t_lims		lims;
	t_ramp		ramp;
	t_pred_rots	fwd;
	t_pred_rots	bwd;
}				t_stack;

typedef struct s_all
{
	t_stack			a;
	t_stack			b;
	t_cmds			pred_cmds;
	t_cmds			exec_cmds;
	t_cmds			ramp_cmds;
}					t_all;

enum	e_moves
{
	PUSH_B_FWD,
	PUSH_B_BWD,
	SWAP_FWD,
	SWAP_BWD,
};

#endif