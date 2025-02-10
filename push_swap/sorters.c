/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:11:03 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/10 13:16:58 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_u5(t_stack **a, t_stack **b)
{
	
}

void	sort_u3(t_stack **a, t_stack **b)
{
	if (!*a || !(*a)->next)
		return ;
	else if ((*a)->val > (*a)->next->val)
	{
		swap(&a, &b, 'a');
		return ;
	}
	if ((*a)->val < (*a)->next)
		
}

void	insertion_sort(t_stack **a, t_stack **b)
{
	while (1)
	{
		if (is_sorted(t_stack *b))
			break ;

	}
}

void	merge_sort(t_stack **a, t_stack **b)
{
	while (!is_sorted(*a))
	{
		
	}
}

