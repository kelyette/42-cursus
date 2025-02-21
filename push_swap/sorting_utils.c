/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:00:34 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 00:42:55 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack, int rev)
{
	int	d;

	d = 1;
	if (rev)
		d = -1;
	while (stack && stack->next)
	{
		if (stack->val + d != stack->next->val)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	get_msdi(t_stack *s)
{
	int	max;
	int	msdi;

	max = 0;
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

int	get_min_dist(t_stack *a, t_stack *min[2], int dist[2])
{
	int	size;

	size = get_size(a);
	min[0] = get_min(a, 0);
	min[1] = NULL;
	if (size == 5)
		min[1] = get_min(a, min[0]);
	dist[0] = get_dist(a, min[0], 1);
	if (min[1])
		dist[1] = get_dist(a, min[1], 1);
	return (min[1] && ft_abs(dist[0]) > ft_abs(dist[1]));
}

int	get_dist(t_stack *a, t_stack *trgt, int abs)
{
	int	d;
	int	size;

	d = 0;
	size = get_size(a);
	while (a && trgt)
	{
		if (a == trgt && abs && (float)d > (size / 2))
			return (d - size);
		else if (a == trgt)
			return (d);
		a = a->next;
		d++;
	}
	return (0);
}
