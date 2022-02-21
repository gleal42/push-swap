/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predict_ramps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:22:41 by gleal             #+#    #+#             */
/*   Updated: 2022/02/18 18:45:08by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	pred_ramp_rots(t_all *pred, t_all *all, t_elem *ref, int (*valid)(t_elem *, t_elem *, t_lims *))
{
	while (valid(pred->a.head, ref, &pred->a.lims))
	{
		(&all->a.ramp.init_cmds)->pb++;
		pred_lims_update(all->a.ramp.first_nbr, all->b.head, all, pred);
		if (pred->a.head->pos == all->a.ramp.first_nbr->pos)
		{
			place_in_b(all->b.head, pred, pred->a.head, &all->a.ramp.init_cmds);
			if (all->a.ramp.init_cmds.rb || all->a.ramp.init_cmds.rr)
				pred->b.head = pred->b.forw;
			else if (all->a.ramp.init_cmds.rrb || all->a.ramp.init_cmds.rrr)
				pred->b.head = pred->b.rev;
		}
		else
			pred_other_rots(pred, all, &all->a.ramp.init_cmds);	
		iterate_stack(&pred->a.head, all->a.head);
	}
}

/* We need:
* To have something to update the
* current b (because when we rotate the head changes)
* To keep track of the numbers we have
* already pushed (in case we need to go backwards)
*/
/*		check_if_found_rot(pred->a.head, &all->b, &pred->b.near_rot, pred->b.lims);
		iterate_fwd_rev_noend(&pred->b, all->b.head);*/

int	pred_other_rots(t_all *pred, t_all *all, t_cmds *temp_cmd)
{
	t_cmds	rot_pred;
	t_elem	*target_fwd;
	t_elem	*target_bwd;

	pred->b.near_rot.r = 0;
	pred->b.near_rot.rrev = 0;
	ft_bzero(&rot_pred, sizeof(t_cmds));
	if (!all->b.head || !all->b.head->next)
	{
		pred_all_inirotsb(all, pred, &rot_pred);
		calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
		temp_cmd->rb += rot_pred.rb;
		temp_cmd->rrb += rot_pred.rrb;
		return (0);
	}
	init_stacks_iteration(&pred->b, pred->a.head);
	target_fwd = pred->b.head;
	target_bwd = pred->b.head->prev;
	while (pred->b.forw->pos != pred->a.head->pos || pred->b.rev->pos != pred->a.head->pos)
	{
		if (pred->b.forw->pos != pred->a.head->pos)
		{
			if (target_fwd->pos != pred->b.head->pos)
				rot_pred.rb++;
			add_rbs(all, pred, &target_fwd, &rot_pred);
		}
		if (pred->b.rev->pos != pred->a.head->pos)
		{
			rot_pred.rrb++;
			add_rrbs(all, pred, &target_bwd, &rot_pred);
		}
	}
	if (rot_pred.rb <= rot_pred.rrb)
	{
		pred->b.near_rot.r = 1;
		pred->b.head = target_fwd;
	}
	else
	{
		pred->b.near_rot.rrev = 1;
		iterate_stack(&target_bwd, all->a.head);
		pred->b.head = target_bwd;
	}
	calculate_initial_pushmoves(pred->b.near_rot.r, pred->b.near_rot.rrev, &rot_pred);
	temp_cmd->rb += rot_pred.rb;
	temp_cmd->rrb += rot_pred.rrb;
	return (0);
}

void	add_rbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_fwd;
	t_elem	*prev_fwd;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	check_fwd = pred->b.forw;
	prev_fwd = check_fwd;
	while (pred->b.forw->pos != pred->a.head->pos
		&& pred->b.forw->pos != (*target)->pos)
	{
		if (is_smaller_than(sent_stack, pred->b.forw,
				pred->b.lims.min, pred->b.lims.max)
				&& is_smaller_than(check_fwd, sent_stack, pred->b.lims.min, pred->b.lims.max))
			check_fwd = sent_stack;
		iterate_stack(&sent_stack, all->a.head);
		if (sent_stack->pos == pred->a.head->pos)
		{
			if (check_fwd->pos == prev_fwd->pos)
			{
				if (is_bigger_than(check_fwd, *target, pred->b.lims.min, pred->b.lims.max))
				{
					pred->b.forw = *target;
					iterate_stack(target, all->b.head);
				}
				else
					pred->b.forw = pred->a.head;
			}
			else
			{
				pred->b.forw = check_fwd;
				prev_fwd = check_fwd;
				rot_pred->rb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
	}
}

/* este foi copiado de cima, ver se faz sentido
ou que modificações é preciso fazer.
utilizar os prev era top
 */

void	add_rrbs(t_all *all, t_all *pred, t_elem **target, t_cmds *rot_pred)
{
	t_elem	*check_bwd;
	t_elem	*prev_bwd;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	check_bwd = pred->b.rev;
	prev_bwd = check_bwd;
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != (*target)->pos)
	{
		if (is_bigger_than(sent_stack, pred->b.rev,
				pred->b.lims.min, pred->b.lims.max)
				&& is_bigger_than(check_bwd, sent_stack, pred->b.lims.min, pred->b.lims.max))
			check_bwd = sent_stack;
		iterate_stack(&sent_stack, all->a.head);
		if (sent_stack->pos == pred->a.head->pos)
		{
			if (check_bwd->pos == prev_bwd->pos)
			{
				if (is_smaller_than(check_bwd, *target, pred->b.lims.min, pred->b.lims.max))
				{
					pred->b.rev = *target;
					(*target) = (*target)->prev;
				}
				else
					pred->b.rev = pred->a.head;
			}
			else
			{
				pred->b.rev = check_bwd;
				prev_bwd = check_bwd;
				rot_pred->rrb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
	}
}

//update_pred_lims_b(&lims_b, all->a.ramp.first_nbr, check_fwd, all->b.head);

void	update_pred_lims_b(t_all *all, t_lims *lims_b, t_elem *check)
{
	int min;
	int max;
	t_elem	*temp;

	temp = all->b.head;
	min = 0;
	max = 0;
	while (temp)
	{
		if (!min || temp->pos < min)
			min = temp->pos;
		if (!max || temp->pos > max)
			max = temp->pos;
		temp = temp->next;
	}
	temp = all->a.ramp.first_nbr;
	while (temp && temp->pos != check->pos)
	{
		if (!min || temp->pos < min)
			min = temp->pos;
		if (!max || temp->pos > max)
			max = temp->pos;
		
		temp = temp->next;
	}
	lims_b->max = max;
	lims_b->min = min;
}

/*void	pred_start_rbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*check_fwd;
	t_elem	*prev_fwd;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	check_fwd = pred->b.forw;
	prev_fwd = check_fwd;
	while (pred->b.forw->pos != pred->a.head->pos
		&& pred->b.forw->pos != pred->b.head->pos)
	{
		if (is_smaller_than(sent_stack, pred->b.forw,
				pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check_fwd->pos)
			check_fwd = sent_stack;
		if (sent_stack->pos == pred->a.head->prev->pos)
		{
			if (check_fwd->pos == prev_fwd->pos)
			{
				if (is_bigger_than(check_fwd, pred->b.head, pred->b.lims.min, pred->b.lims.max))
					pred->b.forw = pred->b.head;
				else
					pred->b.forw = pred->a.head;
			}
			else
			{
				pred->b.forw = check_fwd;
				rot_pred->rb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
		iterate_stack(&sent_stack, all->a.head);
	}
}

void	pred_start_rrbs(t_all *all, t_all *pred, t_cmds *rot_pred)
{
	t_elem	*check_bwd;
	t_elem	*prev_bwd;
	t_elem	*sent_stack;

	sent_stack = all->a.ramp.first_nbr;
	check_bwd = pred->b.forw;
	prev_bwd = check_bwd;
	while (pred->b.rev->pos != pred->a.head->pos
		&& pred->b.rev->pos != pred->b.head->pos)
	{
		if (is_bigger_than(sent_stack, pred->b.rev,
				pred->b.lims.min, pred->b.lims.max)
				&& sent_stack->pos > check_bwd->pos)
			check_bwd = sent_stack;
		if (sent_stack->pos == pred->a.head->prev->pos)
		{
			if (check_bwd->pos == prev_bwd->pos)
			{
				if (is_smaller_than(check_bwd, pred->b.head, pred->b.lims.min, pred->b.lims.max))
					pred->b.rev = pred->b.head->prev;
				else
					pred->b.rev = pred->a.head;
			}
			else
			{
				pred->b.rev = check_bwd;
				rot_pred->rrb++;
				sent_stack = all->a.ramp.first_nbr;
			}
		}
		iterate_stack(&sent_stack, all->a.head);
	}
}*/
/*
* Consider the numbers that were already pushed in case the next number
* Check if it is considering the right numbers
*/
