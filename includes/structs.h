/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:49:21 by gleal             #+#    #+#             */
/*   Updated: 2022/02/12 21:12:15 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_rot
{
	int			r;
	int			rrev;
}				t_rot;

typedef struct s_limits
{
	int			min;
	int			max;
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

typedef struct s_elem
{
	int				nbr;
	int				pos;
	struct s_elem	*prev;
	struct s_elem	*next;
}				t_elem;

typedef struct s_ramp
{
	t_cmds	init_cmds;
	t_cmds	best_cmds;
	t_elem	*first_nbr;
	t_elem	*off_nbr;
}				t_ramp;

typedef struct s_stack
{
	t_elem		*head;
	t_elem		*forw;
	t_elem		*rev;
	t_rot		ini_rot;
	t_limits	lims;
	t_ramp		ramp;
}				t_stack;

typedef struct s_all
{
	t_stack			a;
	t_stack			b;
	t_cmds			exec_cmds;
}					t_all;

enum	e_moves
{
	PUSH_B_FWD,
	PUSH_B_BWD,
	SWAP_FWD,
	SWAP_BWD,
	PUSH_BACK
};

#endif