/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:00:34 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/05 21:08:23 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack)
	{
		if (stack->val > stack->next->val)
			return (0);
		stack = stack->next;
	}
	return (1);
}
