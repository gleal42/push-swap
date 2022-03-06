/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:02:41 by gleal             #+#    #+#             */
/*   Updated: 2022/03/06 17:19:22 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "predict.h"


/*
** I predict the moves needed to join 2 subsections in order to minimize them
** 1 3 6 2 4 7 I can either:
** 			3 ra to 2 and push 2 and 4 => 5 moves
** 			2 ra to 6 and push 6 and 2 => 4 moves
** 			1 ra to 3 and push 3 6 => 3 moves
** 			push 1 3 6 => 3 moves
** @param:	- [t_all *] struct with all the variables
** 			- [int] Number of numbers to sort (e.g. 100 numbers)
** 			- [t_elem *] first number in 2nd subsection
** Line-by-line comments:
** @3		predict all moves to join subsections starting in 
** 			all->a.ramp.first_nbr
** @12-13	all->a.ramp.first_nbr starts one number before
*/

void	pred_rot_b_analysis(t_all *all, t_elem *firstinramp, int n)
{
	while (1)
	{
		pred_ramp_moves(all, firstinramp);
		if (is_better_ramp(all, firstinramp, n))
		{
			all->a.ramp.best_cmds = all->a.ramp.init_cmds;
			all->a.ramp.off_nbr = all->a.ramp.first_nbr;
			all->a.ramp.best_pb = all->a.ramp.init_pb;
		}
		if (stop_pred_ramps(all, all->a.ramp.first_nbr))
			break ;
		ramp_start_before(&all->pred_cmds);
		all->a.ramp.first_nbr = all->a.ramp.first_nbr->prev;
		all->a.ramp.init_cmds = all->pred_cmds;
	}
	all->pred_cmds = all->a.ramp.best_pb;
}


/*
** Predict rbs and rrbs 
** (and rrs and rrs in case it is the fst number)
** separated into 2 subsection:
** in case first_nbr is not the first in ramp first we
** predict rots from first_nbr until we reach end of 
** first ramp
** the second subsection we push until the number
** before the one we pushed is in ascending order
** e.g. 1 3 6 2 4 7, if we start in 6 the 2 subsections are
** 1st predict moves for 6 and
** 2nd predict moves for 2 (4 is bigger than 3 (before 6))
** @param:	- [t_all *] struct with all the variables
** 			- [t_elem *] first number in 2nd subsection
** Line-by-line comments:
** @7	predict moves for 1st subsection
** @8	predict moves for 2nd subsection
*/

int	pred_ramp_moves(t_all *all, t_elem *fst)
{
	t_all	pred;

	pred = *all;
	pred.a.head = all->a.ramp.first_nbr;
	pred.b.head = all->b.head;
	all->a.ramp.init_cmds = all->pred_cmds;
	pred_ramp_rots(&pred, all, fst, &fst_ramp_val);
	pred_ramp_rots(&pred, all, all->a.ramp.first_nbr->prev, &scd_ramp_val);
	return (0);
}


/*
** validation to check if we are still in first subsection
** @param:	- [t_elem *] current number we are predicting
**			- [t_elem *] first number in 2nd subsection
** @return:	[int] 1 if we are still in 1st ramp
** Line-by-line comments:
** @1	lims are not used because I tried to use the same function pointer for both
** pred_ramp_rots
*/


int	fst_ramp_val(t_elem *head, t_elem *start_secramp, t_lims *lims)
{
	(void)lims;
	if (head->pos != start_secramp->pos)
		return (1);
	else
		return (0);
}

/*
** validation to check if we are still in first subsection
** @param:	- [t_elem *] current number we are predicting
**			- [t_elem *] first number in 2nd subsection
** @return:	[int] 1 if we are still in 1st ramp
** Line-by-line comments:
** @1	being bigger depends on max and min for that stack
** 1 2 3 => 1 is bigger than 3
*/

int	scd_ramp_val(t_elem *head, t_elem *start_fstramp, t_lims *lims)
{
	if (is_bigger_than(start_fstramp, head, lims->min, lims->max))
		return (1);
	else
		return (0);
}


/*
** first we add a pb to predicted commands.
** then for the first number in ramp we try to look for rrs and rrrs
** for the rest of the ramp we need to predict the number of rbs
** and rrbs necessary depending on the number that was pushed previously
** (current position) as well as the remaining numbers pushed
** a  b
** 10 1
** 25 48
** 46 47 
** 57 30
** 36  
** here if we were to push 46 and 57, we need to take into consideration that
** 46 will be placed between 47 and 30 and if when we predict the rotates for 57
** if we need to consider the rrb from 46 to 47
** @param:	- [t_all *] copy of all struct for this prediction
** 			- [t_all *] struct with all the variables
** 			- [t_elem *] either the first number of second ramp
** 			or the number before the first number we push
**			(used as references for fst and 2nd ramp val)
** 			- [int *] 1st and 2nd ramp validations
** Line-by-line comments:
** @3		add 1 pb
** @4-14	if first number pushed predict rr and rrr
** @16		if not first number then complex prediction
*/


void	pred_ramp_rots(t_all *pred, t_all *all,
		t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (valid(pred->a.head, ref, &pred->a.lims))
	{
		add_update_cmd(&all->a.ramp.init_cmds.pb, &all->a.ramp.init_cmds, 1);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		{
			place_in_b_rots(all->b.head, pred, pred->a.head,
				&all->a.ramp.init_cmds);
			all->a.ramp.init_pb = all->a.ramp.init_cmds;
			if (all->a.ramp.init_cmds.rb || all->a.ramp.init_cmds.rr)
				pred->b.head = pred->b.forw;
			else if (all->a.ramp.init_cmds.rrb || all->a.ramp.init_cmds.rrr)
				pred->b.head = pred->b.rev;
			init_stacks_iteration(&pred->b, pred->b.head);
		}
		else
			pred_other_rots(pred, all, &all->a.ramp.init_cmds);
		if (all->a.ramp.best_cmds.total
			&& all->a.ramp.init_cmds.total > all->a.ramp.best_cmds.total)
			return ;
		pred_lims_update(all->a.ramp.first_nbr, pred->b.head, all, pred);
		iterate_stack(&pred->a.head, all->a.head);
	}
}
