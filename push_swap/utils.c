/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:27:55 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/19 14:02:54 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

int	atoi_check(char *str, int *ptr)
{
	int	res;

	res = 0;
	*ptr = 1;
	while (*str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			*ptr = -1;
	while (*str && res != INT_MAX && res != INT_MIN)
	{
		if (!ft_isdigit(*str) && *str != ' '
			&& ft_printf("Error\n"))
			return (1);
		if (res == INT_MAX / 10 && *str > ('7' + *ptr == -1)
			&& ft_printf("Error\n"))
			return (1);
		res = res * 10 + (*str++ - '0');
	}
	*ptr *= res;
	return (0);
}

t_stack	*get_min(t_stack *s, t_stack *prev)
{
	t_stack	*min;

	min = 0;
	while (s)
	{
		if (!prev || s->baseval > prev->baseval)
			if (!min || s->baseval < min->baseval)
				min = s;
		s = s->next;
	}
	return (min);
}

void	compress_stack(t_stack *s)
{
	int		i;
	int		size;
	t_stack	*min;

	i = 0;
	size = get_size(s);
	min = 0;
	while (i < size)
	{
		min = get_min(s, min);
		min->val = i++;
	}
}

int	is_duplicate(t_stack *s, int val)
{
	while (s)
	{
		if (s->baseval == val)
		{
			ft_printf("Error\n");
			return (1);
		}
		s = s->next;
	}
	return (0);
}
