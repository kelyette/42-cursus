/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 15:10:35 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stacks	s;
	int			len;

	if (argc < 2)
		return (1);
	s.a = init_stack(argv + 1, argc - 1);
	s.b = NULL;
	if (!s.a)
		return (1);
	if (is_sorted(s.a, 0))
	{
		free_stack(s.a);
		return (0);
	}
	len = get_size(s.a);
	if (len <= 3)
		sort_3u(&s.a, len);
	else if (len <= 5)
		sort_5u(&s.a, &s.b, len);
	else
		radixlsd_sort(&s);
	if (s.a)
		free_stack(s.a);
	if (s.b)
		free_stack(s.b);
}
