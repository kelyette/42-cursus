/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 00:43:20 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_stacks	s;
	int			len;

	if (argc < 2)
		return (1);
	a = init_stack(argv + 1, argc - 1);
	if (!a)
		return (1);
	b = NULL;
	len = get_size(a);
	s.a = a;
	s.b = b;
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
