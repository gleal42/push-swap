/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:49:21 by gleal             #+#    #+#             */
/*   Updated: 2022/03/04 19:27:43 by gleal            ###   ########.fr       */
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
}				t_cmds;

typedef struct s_elem
{
	int				nbr;
	int				pos;
	struct s_elem	*prev;
	struct s_elem	*next;
}				t_elem;

typedef struct s_stack
{
	t_elem		*head;
	t_elem		*forw;
	t_elem		*rev;
	t_rot		ini_rot;
	t_rot		near_rot;
	t_lims		lims;
}				t_stack;

typedef struct s_all
{
	t_stack			a;
	t_stack			b;
	t_cmds			pred_cmds;
	t_cmds			exec_cmds;
}					t_all;

enum	e_moves
{
	PUSH_B_FWD,
	PUSH_B_BWD,
	SWAP_FWD,
	SWAP_BWD,
};

#endif