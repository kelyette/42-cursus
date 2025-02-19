/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:11:03 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/19 13:58:40 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3u(t_stack **a)
{
	t_stack	*max;
	int		size;

	size = get_size(*a);
	max = get_nth(*a, -1);
	if (size == 3 && (max == (*a) || max == (*a)->next))
		rotate(a, NULL, max == (*a)->next, 'a');
	if ((*a)->val > (*a)->next->val)
		swap(a, NULL, 'a');
}

void	sort_5u(t_stack **a, t_stack **b)
{
	(void)a;
	(void)b;
}

void	sort_a(t_stacks *s, int idx, int len)
{
	while (s->a && len-- > 0)
	{
		if (s->a->val & (1 << idx))
			rotate(&s->a, &s->b, 0, 'a');
		else
			push(&s->a, &s->b, 'b');
		if (is_sorted(s->a, 0) && is_sorted(s->b, 1)
			&& s->b->val == s->a->val - 1)
			return ;
	}
}

void	sort_b(t_stacks *s, int idx, int len)
{
	if (is_sorted(s->b, 1))
		return ;
	while (s->b && len-- > 0)
	{
		if (s->b->val & (1 << idx))
			push(&s->a, &s->b, 'a');
		else
			rotate(&s->a, &s->b, 0, 'b');
	}
}

void	radixlsd_sort(t_stacks *s)
{
	int		idx;
	int		msdi;
	int		len;
	int		rem;

	if (!s->a || !s->a->next)
		return ;
	idx = 0;
	msdi = get_msdi(s->a);
	len = get_size(s->a);
	rem = 0;
	while (idx <= msdi)
	{
		sort_a(s, idx++, len - rem);
		if (is_sorted(s->a, 0) && is_sorted(s->b, 1))
			while (s->b)
				push(&s->a, &s->b, 'a');
		else
		{
			sort_b(s, idx, get_size(s->b));
			rem = get_size(s->b);
		}
		if (!s->b && s->a && is_sorted(s->a, 0))
			return ;
	}
}
