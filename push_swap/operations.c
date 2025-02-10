/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:08:12 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/10 12:57:55 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack **a, t_stack **b, char name)
{
	t_stack	**stack;
	t_stack	*tmp;

	stack = a;
	if (name)
		ft_printf("s%c\n", name);
	if (name == 'b')
		stack = b;
	else if (name == 's')
	{
		swap(a, NULL, 0);
		swap(b, NULL, 0);
		return ;
	}
	else if (name && name != 'a'
		&& ft_printf("swap: unknown operation '%c'\n", name))
		return ;
	if (!*stack || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	tmp->next = *stack;
	*stack = tmp;
}

void	push(t_stack **a, t_stack **b, char name)
{
	t_stack	**src;
	t_stack	**dst;
	t_stack	*tmp;

	src = b;
	dst = a;
	if (name)
		ft_printf("p%c\n", name);
	if (name == 'b')
	{
		src = a;
		dst = b;
	}
	else if (name != 'a')
		return ;
	tmp = *src;
	*src = (*src)->next;
	if (!dst)
		*dst = tmp;
	else
	{
		tmp->next = *dst;
		*dst = tmp;
	}
}

static void	rotate_reverse(t_stack **stack)
{
	t_stack	*tail;
	t_stack	*pretail;

	if (!*stack || !(*stack)->next)
		return ;
	pretail = *stack;
	while (pretail && pretail->next && pretail->next->next)
		pretail = pretail->next;
	tail = pretail->next;
	pretail->next = NULL;
	tail->next = *stack;
	*stack = tail;
}

void	rotate(t_stack **a, t_stack **b, int reverse, char name)
{
	t_stack	**head;
	t_stack	*tail;

	head = a;
	if (name)
		ft_printf("r%s%c\n", &"r"[!reverse], name);
	if (name == 'b')
		head = b;
	else if (name == 'r')
	{
		rotate(a, NULL, reverse, 0);
		rotate(b, NULL, reverse, 0);
		return ;
	}
	if (!*head || !(*head)->next)
		return ;
	if (reverse)
		rotate_reverse(head);
	else
	{
		tail = get_tail(*head);
		tail->next = *head;
		*head = (*head)->next;
		tail->next->next = NULL;
	}
}
