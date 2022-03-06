/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_a_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:46:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 17:48:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*
** Iterate if it is ascending and prepare moves if it is not ascending
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** Line-by-line comments:
** @10-12	1 2 4 3 5 on 4 we would find that the next is descending and good for swap
** @16-18	1 3 6 2 4 7 on 6 we would find that the next is descending
** 			so we need to predict the push moves to join these 2 subsections
** 			starting in the first number of the 2nd subsection (2)
*/

void	analyze_fwd(t_all **all, int n)
{
	if (is_smaller_than((*all)->a.forw, ((*all)->a.forw)->next,
			(*all)->a.lims.min, (*all)->a.lims.max))
		(*all)->a.ini_rot.r++;
	else
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, (*all)->a.forw, (*all)->a.lims.min,
				(*all)->a.lims.max))
		{
			(*all)->pred_cmds.ra = (*all)->a.ini_rot.r;
			swap_a(*all, (*all)->a.head);
			(*all)->a.ini_rot.r++;
		}
		else
		{
			(*all)->a.ini_rot.r++;
			(*all)->pred_cmds.ra = (*all)->a.ini_rot.r;
			merge_ramp_spot(*all, n, (*all)->a.forw->next);
		}
		update_exec_cmds(all, n);
	}
	(*all)->a.forw = (*all)->a.forw->next;
}

/*
** Iterate if it is ascending and prepare moves if it is not ascending
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** Line-by-line comments:
** @10-12	1 2 4 3 5 on 3 we would find that the previous is descending and good for swap
** 			we need to rotate one extra before so that we can swap in the right place
** @16-18	1 3 6 2 4 7 on 2 we would find that the previous is descending
** 			so we need to predict the push moves to join these 2 subsections
** 			starting in the first number of the 2nd subsection (2)
** @20		once we predict the moves we decide if they are better that the previously
** 			predicted moves
*/

void	analyze_bwd(t_all **all, int n)
{
	if (is_bigger_than((*all)->a.rev, (*all)->a.rev->prev,
			(*all)->a.lims.min, (*all)->a.lims.max))
		(*all)->a.ini_rot.rrev++;
	else
	{
		ft_bzero(&(*all)->pred_cmds, sizeof(t_cmds));
		if (is_good_for_swap((*all)->a.head, (*all)->a.rev->prev,
				(*all)->a.lims.min, (*all)->a.lims.max))
		{
			(*all)->a.ini_rot.rrev++;
			(*all)->pred_cmds.rra = (*all)->a.ini_rot.rrev;
			swap_a(*all, (*all)->a.head);
		}
		else
		{
			(*all)->pred_cmds.rra = (*all)->a.ini_rot.rrev;
			merge_ramp_spot(*all, n, (*all)->a.rev);
			(*all)->a.ini_rot.rrev++;
		}
		update_exec_cmds(all, n);
	}
	(*all)->a.rev = (*all)->a.rev->prev;
}


/*
** here I created 2 hypotheses: 
** place_in_b_rots for each number we predict the minimum number of moves 
** (using rr and rrrs) necessary to be placed in b in descending position
**
** pred_rot_b_analysis I predict all the moves necessary to join 2 subsections
** however this 2nd hypothesis didn't work as expected (500 moves 10 seconds
** to predict and even more moves that place_in_b_rots)
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** 			- [t_elem *] first number in 2nd subsection
** 			1 3 6 2 4 7 (would be) number 2
*/

void	merge_ramp_spot(t_all *all, int n, t_elem *firstinramp)
{
	all->a.ramp.first_nbr = firstinramp;
	all->a.ramp.init_cmds = all->pred_cmds;
	all->a.ramp.off_nbr = firstinramp;
	ft_bzero(&(all->a.ramp.best_cmds), sizeof(t_cmds));
	if (1)
	{
		place_in_b_rots(all->b.head, all, all->a.ramp.first_nbr,
			&all->pred_cmds);
		add_update_cmd(&all->pred_cmds.pb, &all->pred_cmds, 1);
	}
	else
		pred_rot_b_analysis(all, firstinramp, n);
}


/*
** if ra and rb then rr
** if rra and rrb then rrr
** if all ra and rra were converted then increase rb and rrb
** @param:	- [t_elem *] elem on top of b
**			- [t_all *] struct with all the variables
**			- [t_elem *] number that will be placed in b
**			- [t_cmds *] table of commands with the 
**			correct ra or rra to get to move
** @return:	[type] return_value
** Line-by-line comments:
** @line-line	comment
*/

void	place_in_b_rots(t_elem *b, t_all *all, t_elem *move, t_cmds *cmds)
{
	all->b.near_rot.r = 0;
	all->b.near_rot.rrev = 0;
	init_push_b(cmds);
	if (is_good_to_place_wo_rot_b(b, move, all->b.lims))
		return ;
	init_stacks_iteration(&all->b, b);
	iterate_fwd_rev_toend(&all->b);
	while (all->b.forw)
	{
		add_double_rots_a(cmds);
		check_if_found_rot_a(move, &all->b, &all->b.near_rot, all->b.lims);
		if (all->b.near_rot.r || all->b.near_rot.rrev)
			break ;
		iterate_fwd_rev_toend(&all->b);
	}
	calculate_initial_pb_moves(all->b.near_rot.r, all->b.near_rot.rrev, cmds);
}

void	swap_a(t_all *all, t_elem *a)
{
	if (all->pred_cmds.ra)
		all->pred_cmds.type = SWAP_FWD;
	else
		all->pred_cmds.type = SWAP_BWD;
	all->pred_cmds.sa = 1;
	all->pred_cmds.total = count_moves(&all->pred_cmds);
	if (!a || !a->next)
		return ;
	if (!a->next->next && a->pos < a->next->pos)
	{
		all->pred_cmds.sa = 0;
		all->pred_cmds.ss = 1;
	}
}
