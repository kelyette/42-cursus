/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:46:48 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 00:54:54 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(char **nums, int count)
{
	t_stack	*stack;
	int		i;
	int		do_free;

	do_free = count == 1;
	if (count == 1)
	{
		count = 0;
		nums = ft_split(nums[0], ' ');
		while (nums[count])
			count++;
	}
	stack = NULL;
	i = 0;
	while (nums[i] && i < count)
	{
		if (add_node(&stack, nums[i++])
			&& ((do_free && error_free(stack, nums, 1))
				|| error_free(stack, NULL, 1)))
			return (NULL);
	}
	if (do_free)
		ft_free_split(nums);
	compress_stack(stack);
	return (stack);
}

int	add_node(t_stack **s, char *val)
{
	t_stack	*tail;
	t_stack	*node;
	int		ival;

	tail = get_tail(*s);
	if (atoi_check(val, &ival) || is_duplicate(*s, ival))
		return (1);
	node = ft_calloc(1, sizeof(t_stack));
	if (!node)
		return (1);
	node->baseval = ival;
	if (tail)
		tail->next = node;
	else
		*s = node;
	return (0);
}

t_stack	*get_tail(t_stack *stack)
{
	while (stack && stack->next)
		stack = stack->next;
	return (stack);
}

int	get_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack && ++size)
		stack = stack->next;
	return (size);
}

void	free_stack(t_stack *s)
{
	t_stack	*next;

	while (s)
	{
		next = s->next;
		free(s);
		s = next;
	}
}
