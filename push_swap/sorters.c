/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:11:03 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 00:59:06 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3u(t_stack **a, int size)
{
	t_stack	*s;
	t_stack	*max;

	if (size <= 1)
		return ;
	s = *a;
	max = NULL;
	while (s)
	{
		if (!max || max->val < s->val)
			max = s;
		s = s->next;
	}
	if (size == 3 && (max == (*a) || max == (*a)->next))
		rotate(a, NULL, max == (*a)->next, 'a');
	if ((*a)->val > (*a)->next->val)
		swap(a, NULL, 'a');
}

void	sort_5u(t_stack **a, t_stack **b, int size)
{
	t_stack	*min[2];
	int		dist[2];
	int		closest;

	closest = get_min_dist(*a, min, dist);
	while (size != 3)
	{
		if ((*a == min[closest]) && size--)
		{
			push(a, b, 'b');
			closest ^= 1;
			dist[closest] = get_dist(*a, min[closest], 1);
		}
		else if (dist[closest] == 1)
			swap(a, b, 'a');
		else
			rotate(a, b, dist[closest] < 1, 'a');
	}
	if ((*b)->next && (*b)->val < (*b)->next->val)
		swap(a, b, 'b');
	sort_3u(a, 3);
	push(a, b, 'a');
	if (min[1])
		push(a, b, 'a');
}

static int	sort_a(t_stacks *s, int idx, int len)
{
	while (s->a && len-- > 0)
	{
		if (s->a->val & (1 << idx))
			rotate(&s->a, &s->b, 0, 'a');
		else
			push(&s->a, &s->b, 'b');
		if (is_sorted(s->a, 0) && is_sorted(s->b, 1)
			&& (!s->b || s->b->val == s->a->val - 1))
		{
			while (s->b)
				push(&s->a, &s->b, 'a');
			return (1);
		}
	}
	return (0);
}

static void	sort_b(t_stacks *s, int idx, int len)
{
	if (!s->b)
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
	while (idx < msdi)
	{
		if (!sort_a(s, idx++, len - rem))
		{
			sort_b(s, idx, get_size(s->b));
			rem = get_size(s->b);
		}
		if (!s->b && s->a && is_sorted(s->a, 0))
			return ;
	}
}
