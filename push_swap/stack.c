/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:46:48 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/05 20:57:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(char **nums, int count)
{
	t_stack	*stack;
	t_stack	*head;

	stack = new_node(0);
	head = stack;
	if (atoi_check(*nums++, &stack->val))
		return (NULL);
	while (--count)
	{
		stack->next = new_node(0);
		stack = stack->next;
		if (atoi_check(*nums++, &stack->val))
			return (NULL);
	}
	return (head);
}

t_stack	*new_node(int val)
{
	t_stack	*node;

	if (!val)
		return (ft_calloc(sizeof(t_stack), 1));
	node = ft_calloc(sizeof(t_stack), 1);
	node->val = val;
	return (node);
}

t_stack	*get_tail(t_stack *stack)
{
	while (stack && stack->next)
		stack = stack->next;
	return (stack);
}

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
