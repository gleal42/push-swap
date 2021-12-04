/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:11:18 by gleal             #+#    #+#             */
/*   Updated: 2021/11/21 23:51:23 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap_utils.h"

//similar to place in b but we also predict those that were previously pushed
/*
*	okay aqui tu ves os numeros que já foram atraves do first nbr e daquele em que estamos
*	atenção que aqui é só para acrescentar os rbs que estao entre dois numeros caso existam
*	ou seja é só umna mini operação
*/

void	add_rbs(t_stack *first_nbr, t_stack *rev_b, t_cmds *nbr_rot_pred)
{
	(void) first_nbr;
	(void) rev_b;
	nbr_rot_pred->rb++;
	return ;
	// (void)update_predict_limits(first_nbr, cur_a, cur_b, a, b, pred_limits);
	//add something to check if current position was already used in previous pushes
}

void	add_rrbs(t_stack *first_nbr, t_stack *forw_b, t_cmds *nbr_rot_pred)
{
	t_stack *temp;

	(void) first_nbr;
	(void) forw_b;
	temp = forw_b;
	nbr_rot_pred->rrb++;
	return ;
	// update_predict_limits(first_nbr, cur_a, cur_b, a, b, pred_limits);
	//add something to check if current position was already used in previous pushes
}

void update_position_and_total(t_stack *b, int has_rb, int has_rrb, t_cmds *cmds, t_stack *cur_stack, t_stack **cur_b, t_limits *limits)
{
	int fwd_total;
	int rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (has_rb)
		fwd_total = cmds->ra + cmds->rr + cmds->rra + cmds->rrr + cmds->rb + cmds->pb;
	if (has_rrb)
		rev_total = cmds->ra + cmds->rr + cmds->rra + cmds->rrr + cmds->rrb + cmds->pb;
	if ((fwd_total <= rev_total && has_rb)|| !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
		while (b->next && !(is_next_nbr_bigger(cur_stack, (*cur_b)->prev, limits->min_b, limits->max_b)
			&& is_prev_nbr_smaller(cur_stack, *cur_b, limits->min_b, limits->max_b)))
		{
			if ((*cur_b)->next)
				*cur_b = (*cur_b)->next;
			else
				*cur_b = b;
		}
	}
	else if ((fwd_total > rev_total && has_rrb) || !has_rb)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
		while (b->next && !(is_next_nbr_bigger(cur_stack, (*cur_b)->prev, limits->min_b, limits->max_b)
			&& is_prev_nbr_smaller(cur_stack, *cur_b, limits->min_b, limits->max_b)))
			*cur_b = (*cur_b)->prev;
	}
}

/* cur stack 4 não está a funcionar.
b merge ramp spot antes de mais
aqui tem demasiadas coisas. Aqui para é só para prever rbs e rrbs 
(ver se dá paara delete a parte dos ra e rra*/

int	rot_moves_curnbr(t_cmds *temp_cmd, t_stack *a, t_stack *b, t_stack *first_nbr, t_stack *cur_stack, t_stack *cur_b, t_all *temp, t_limits *limits)
{
	t_cmds	nbr_rot_pred;
	int has_rb;
	int has_rrb;
	int rev_total;

	nbr_rot_pred = *temp_cmd;
	nbr_rot_pred.rb = 0;
	nbr_rot_pred.rrb = 0;
	nbr_rot_pred.rr = 0;
	nbr_rot_pred.rrr = 0;
	rev_total = 0;
	has_rb = 0;
	has_rrb = 0;
	(void)a;
	if (!cur_b->next)
	{
		has_rb++;
		update_position_and_total(b, has_rb, has_rrb, &nbr_rot_pred, cur_stack, &cur_b, limits);
		return (0);
	}
	if (is_next_nbr_bigger(cur_stack, cur_b->prev, limits->min_b, limits->max_b)
			&& is_prev_nbr_smaller(cur_stack, cur_b, limits->min_b, limits->max_b))
	{
		if (nbr_rot_pred.ra || (!nbr_rot_pred.ra && !nbr_rot_pred.rra))
			has_rb++;
		else if (nbr_rot_pred.rra)
			has_rrb++;
	}
	temp->forw_b = cur_b->next;
	temp->rev_b = cur_b->prev->prev;
	while (!has_rb || !has_rrb)
	{
		if (!has_rb)
		{
			if(nbr_rot_pred.rb > 0)
			{
				nbr_rot_pred.rra--;
				nbr_rot_pred.rr++;
			}
			else
				add_rbs(first_nbr, temp->forw_b, &nbr_rot_pred);
			if (is_next_nbr_bigger(cur_stack, temp->forw_b->prev, limits->min_b, limits->max_b)
			&& is_prev_nbr_smaller(cur_stack, temp->forw_b, limits->min_b, limits->max_b))
				has_rb++;
		}
		if (!has_rrb)
		{
			if(nbr_rot_pred.rra > 0)
			{
				nbr_rot_pred.rra--;
				nbr_rot_pred.rrr++;
			}
			else
				add_rrbs(first_nbr, temp->rev_b, &nbr_rot_pred);
			if (temp->rev_b->next)
			{
				if (is_next_nbr_bigger(cur_stack, temp->rev_b, limits->min_b, limits->max_b)
			 && is_prev_nbr_smaller(cur_stack, temp->rev_b->next, limits->min_b, limits->max_b))
					has_rrb++;
			}
			else
			{
				if (is_next_nbr_bigger(cur_stack, temp->rev_b, limits->min_b, limits->max_b)
			 && is_prev_nbr_smaller(cur_stack, b, limits->min_b, limits->max_b))
					has_rrb++;
			}
		}
		if (!has_rb)
		{
			if (temp->forw_b->next)
				temp->forw_b = temp->forw_b->next;
			else
				temp->forw_b = b;
		}
		if (!has_rrb)
			temp->rev_b = (temp->rev_b)->prev;
	}
	update_position_and_total(b, has_rb, has_rrb, &nbr_rot_pred, cur_stack, &cur_b, limits);
	temp_cmd->rb += nbr_rot_pred.rb;
	temp_cmd->rrb += nbr_rot_pred.rrb;
	temp_cmd->rr += nbr_rot_pred.rr;
	temp_cmd->rrr += nbr_rot_pred.rrr;
	return (0);
}

void update_predict_limits(t_stack *first_nbr, t_stack *cur_a, t_stack *cur_b, t_stack *a, t_stack *b, t_all *pred_limits)
{
	(void)a;
	if (first_nbr->prev->pos == cur_a->pos)
	{
		pred_limits->lims.max_b = 0;
		pred_limits->lims.min_b = 0;
	}
	else
	{
		if (cur_a->pos == pred_limits->lims.max_a)
			pa_predict_adjust_max_a(b, cur_b, &pred_limits->lims);
		if (cur_a->pos == pred_limits->lims.min_a)
			pa_predict_adjust_min_a(b, cur_b, &pred_limits->lims);
	}
	if (!b)
	{
		pred_limits->lims.max_b = cur_a->pos;
		pred_limits->lims.min_b = cur_a->pos;
	}
	else
	{
		if (cur_a->pos > pred_limits->lims.max_b)
			pred_limits->lims.max_b = cur_a->pos;
		else if (cur_a->pos < pred_limits->lims.min_b)
			pred_limits->lims.min_b = cur_a->pos;
	}
}

// perceber porque 4 não está a ser apanhado no has_rb
// also perceber porque merge_ramp 5 vez depois do nove o 5 está a ficar com tantos rras ao passar aqui pelo o predict

int	predict_rotate_b_moves(t_stack *first_nbr, t_stack *last_nbr, t_stack *a, t_stack *b, t_cmds *temp_cmd, t_all *temp)
{
	t_stack	*cur_a;
	t_stack	*cur_b;
	t_limits	pred_limits;

	cur_a = first_nbr;
	cur_b = b;
	pred_limits=temp->lims;
	while (cur_a->pos != last_nbr->pos)
	{
		temp_cmd->pb++;
		if (b)
			rot_moves_curnbr(temp_cmd, a, b, first_nbr, cur_a, cur_b, temp, &pred_limits);
		if (!cur_a->next)
			cur_a = a;
		else
			cur_a = cur_a->next;
	}
	while (!is_next_nbr_bigger(cur_a, last_nbr, pred_limits.min_a, pred_limits.max_a))
	{
		temp_cmd->pb++;
		if (b)
			rot_moves_curnbr(temp_cmd, a, b, first_nbr, cur_a, cur_b, temp, &pred_limits);
		if (!cur_a->next)
			cur_a = a;
		else
			cur_a = cur_a->next;
	}
	return (0);
}

int	continue_ramp_analysis(t_stack *a, t_stack	*first_nbr, t_all *temp)
{
	(void)a;
	if (is_prev_nbr_smaller(first_nbr, first_nbr->prev, temp->lims.min_a, temp->lims.max_a))
		return (1);
	else
		return (0);
}

int	have_analyzed_enough(t_cmds off, t_rot_a ini_rot_a, t_stack *forw_a, t_stack *rev_a)
{
	if (off.total)
	{
		if (off.total < ini_rot_a.ra)
			return (1);
		if (off.total < ini_rot_a.rra)
			return (1);
		if (!forw_a)
			return (1);
		if (forw_a->pos == rev_a->pos)
			return (1);
	}
	return (0);
}

int is_temp_better(t_cmds temp, t_cmds off)
{	
	if (!(off.total))
		return (1);
	if(temp.type == SWAP_BWD || temp.type == SWAP_FWD)
	{
		if(off.type == PUSH_B_BWD || off.type == PUSH_B_FWD) 
		{
			if (temp.total < off.total + 2)
				return (1);
			else
				return (0);
		}
		else
		{
			if (temp.total < off.total)
				return (1);
			else
				return (0);
		}
	}
	if (temp.total < off.total)
		return (1);
	else
		return (0);
}

int		is_good_for_swap(t_stack *first, t_stack *to_be_swaped, int min_stack, int max_stack)
{
	if (!first)
		return (0);
	if (!first->next)
		return (0);
	if (!first->next->next)
		return (0);
	if (!to_be_swaped->next)
	{
		if (is_next_nbr_bigger(to_be_swaped, first->next, min_stack, max_stack)
			&& is_prev_nbr_smaller(first,to_be_swaped->prev, min_stack, max_stack))
			return (1);
	}
	else
	{
		if (!to_be_swaped->next->next)
		{
			if (is_next_nbr_bigger(to_be_swaped, first, min_stack, max_stack)
				&& is_prev_nbr_smaller(to_be_swaped->next, to_be_swaped->prev, min_stack, max_stack))
				return (1);
		}
		else
		{
			if (is_next_nbr_bigger(to_be_swaped, to_be_swaped->next->next, min_stack, max_stack)
				&& is_prev_nbr_smaller(to_be_swaped->next, to_be_swaped->prev, min_stack, max_stack))
				return (1);
		}
	}
	return (0);
}

int	count_moves(t_cmds *cmds)
{
	int total;

	total = 0;
	total += cmds->sa;
	total += cmds->sb;
	total += cmds->ss;
	total += cmds->ra;
	total += cmds->rb;
	total += cmds->rr;
	total += cmds->pa;
	total += cmds->pb;
	total += cmds->rra;
	total += cmds->rrb;
	total += cmds->rrr;
	return (total);
}

int	is_next_nbr_bigger(t_stack *cur, t_stack *next_one, int min_stack, int max_stack)
{
	if (!next_one)
		return (1);
	if (cur->pos <= min_stack && next_one->pos >= max_stack)
			return (0);
	if(next_one->pos > cur->pos)
		return (1);
	if (cur->pos >= max_stack && next_one->pos <= min_stack)
		return (1);
	return (0);
}

int	is_prev_nbr_smaller(t_stack *cur, t_stack *prev_one, int min_stack, int max_stack)
{
	if (!prev_one)
		return (1);
	if (cur->pos >= max_stack && prev_one->pos <= min_stack)
			return (0);
	if (prev_one->pos < cur->pos)
		return (1);
	if (cur->pos <= min_stack && prev_one->pos >= max_stack)
		return (1);
	return (0);
}

//maybe add different validations?

int	is_good_position_forward_diff_stack(t_stack *cur, t_stack *next_one, int min_stack, int max_stack)
{
	if (!next_one)
		return (1);
	if (cur->pos <= min_stack && next_one->pos >= max_stack)
			return (0);
	if(next_one->pos > cur->pos)
		return (1);
	if (cur->pos >= max_stack && next_one->pos <= min_stack)
		return (1);
	return (0);
}

int	is_good_position_backward_diff_stack(t_stack *cur, t_stack *prev_one, int min_stack, int max_stack)
{
	if (!prev_one)
		return (1);
	if (cur->pos >= max_stack && prev_one->pos <= min_stack)
			return (0);
	if (prev_one->pos < cur->pos)
		return (1);
	if (cur->pos <= min_stack && prev_one->pos >= max_stack)
		return (1);
	return (0);
}

void	init_rot_b(t_all *all)
{
	all->ini_rot_b.rb = 0;
	all->ini_rot_b.rrb = 0;
}

void	init_rot_a(t_all *all)
{
	all->ini_rot_a.ra = 0;
	all->ini_rot_a.rra = 0;
}

void	init_cmd_list(t_cmds *cmds)
{
	cmds->sa = 0;
	cmds->sb = 0;
	cmds->ss = 0;
	cmds->ra = 0;
	cmds->rb = 0;
	cmds->rr = 0;
	cmds->pa = 0;
	cmds->pb = 0;
	cmds->rra = 0;
	cmds->rrr = 0;
	cmds->rrb = 0;
	cmds->total = 0;
	cmds->type = 0;
}

int	is_input_integer(char **stack_a_args)
{
	int i;

	i = 0;
	if (!stack_a_args[0])
		return (0);
	while (stack_a_args[i])
	{
		if (!is_integer(stack_a_args[i]))
		{

			printf("Error\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	biggest_str_len(char **strs)
{
	int i;
	int len;
	int temp;

	i = 0;
	len = 0;
	if (!strs)
		return 0;
	while (strs[i])
	{
		temp = ft_strlen(strs[i]);
		if (temp > len)
			len = temp;
		i++;
	}
	return (len);
}

void calculate_initial_pushmoves(int has_rb, int has_rrb, t_cmds *cmds)
{
	int fwd_total;
	int rev_total;

	rev_total = 0;
	fwd_total = 0;
	if (has_rb)
		fwd_total = cmds->ra + cmds->rr + cmds->rra + cmds->rrr + cmds->rb + cmds->pb;
	if (has_rrb)
		rev_total = cmds->ra + cmds->rr + cmds->rra + cmds->rrr + cmds->rrb + cmds->pb;
	if ((fwd_total <= rev_total && has_rb)|| !has_rrb)
	{
		cmds->rrb = 0;
		cmds->rra += cmds->rrr;
		cmds->rrr = 0;
		cmds->total = fwd_total;
	}
	else if ((fwd_total > rev_total && has_rrb) || !has_rb)
	{
		cmds->rb = 0;
		cmds->ra += cmds->rr;
		cmds->rr = 0;
		cmds->total = rev_total;
	}
}
