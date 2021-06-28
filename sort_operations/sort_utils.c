/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:17:08 by gleal             #+#    #+#             */
/*   Updated: 2021/06/28 22:53:35 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sort_operations.h"

int		operation_sa(t_list **a)
{
	t_list *first_lst;
	t_list *third_lst;

	if (*a == 0 || (*a)->next == 0)
		return (0);
	first_lst = *a;
	third_lst = (*a)->next->next;
	*a = (*a)->next;
	(*a)->next = first_lst;
	(*a)->next->next = third_lst;
	return (0);
}