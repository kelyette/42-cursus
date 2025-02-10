/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:04 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/10 12:56:01 by kcsajka          ###   ########.fr       */
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
	print_stacks(a, b);
	swap(&a, &b, 'a');
	print_stacks(a, b);
	push(&a, &b, 'b');
	push(&a, &b, 'b');
	push(&a, &b, 'b');
	print_stacks(a, b);
	swap(&a, &b, 'a');
	print_stacks(a, b);
	push(&a, &b, 'a');
	push(&a, &b, 'a');
	push(&a, &b, 'a');
	print_stacks(a, b);
}
