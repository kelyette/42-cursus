/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:00:34 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/19 19:20:54 by kcsajka          ###   ########.fr       */
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

t_stack	*get_nth(t_stack *s, int n)
{
	const int	size = get_size(s);

	if (n == -1 || n > size - 1)
		n = size - 1;
	while (s)
	{
		if (s->val == n)
			return (s);
		s = s->next;
	}
	return (NULL);
}
