/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:11:03 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/14 18:39:03 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_u3(t_stack **a, t_stack **b)
{
	t_stack	*a1;
	t_stack	*a2;
	t_stack	*a3;

	a1 = *a;
	a2 = NULL;
	a3 = NULL;
	if (a1 && a1->next)
		a2 = a1->next;
	if (a2 && a2->next)
		a3 = a2->next;
	if (!a1 || !a2)
		return ;
	if (!a3)
	{
		if (a1->val > a2->val)
			swap(a, b, 'a');
	}
	else if (a1->val < a2->val && a2->val < a3->val)
		return ;
	else if (a1->val > a2->val && a1->val < a3->val)
		swap(a, b, 'a');
	else if (a1->val > a2->val && a2->val > a3->val)
	{
		swap(a, b, 'a');
		rotate(a, b, 0, 'a');
	}
}

void	sort_u5(t_stack **a, t_stack **b)
{
	(void)a;
	(void)b;
}

int	get_msdi(t_stack *s)
{
	int	max;
	int	msdi;

	while (s)
	{
		if (s->val > max)
			max = s->val;
		s = s->next;
	}
	msdi = 0;
	while (max >= (1 << msdi))
		msdi++;
	return (msdi);
}

void	radixlsd_sort(t_stack **a, t_stack **b)
{
	int		idx;
	int		msdi;
	int		len;
	int		rem;

	if (!*a || !(*a)->next)
		return ;
	idx = 0;
	msdi = get_msdi(*a);
	len = get_size(*a);
	while (idx <= msdi)
	{
		rem = len;
		while (rem--)
		{
			if ((*a)->val & (1 << idx))
				rotate(a, b, 0, 'a');
			else
				push(a, b, 'b');
		}
		while (*b)
			push(a, b, 'a');
		idx++;
	}
}
