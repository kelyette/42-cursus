/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/14 18:44:00 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (1);
	a = init_stack(argv + 1, argc - 1);
	if (!a)
		return (1);
	b = NULL;
	radixlsd_sort(&a, &b);
	print_stacks(a, b);
}
