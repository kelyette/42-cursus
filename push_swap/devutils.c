/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:32:59 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/18 16:33:14 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stacks(t_stack *a, t_stack *b)
{
	while (a || b)
	{
		if (a)
		{
			ft_printf("%-2d", a->val);
			a = a->next;
		}
		else
			ft_printf("  ");
		ft_printf(" ");
		if (b)
		{
			ft_printf("%-2d", b->val);
			b = b->next;
		}
		ft_printf("\n");
	}
	ft_printf("--- ---\n a   b\n-------\n");
}

void	print_stacks_bin(t_stack *a, t_stack *b)
{
	int	max;
	int	tmp;

	max = get_msdi(a);
	tmp = get_msdi(b);
	if (tmp > max)
		max = tmp;
	while (a || b)
	{
		if (a)
		{
			ft_printf("%0*b", max, a->val);
			a = a->next;
		}
		else
			ft_printf("%*s", max);
		ft_printf(" ");
		if (b)
		{
			ft_printf("%0*b", max, b->val);
			b = b->next;
		}
		ft_printf("\n");
	}
	ft_printf("---\n");
}
