/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:00 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/14 18:21:56 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include "libft.h"

typedef struct s_stack
{
	int				val;
	struct s_stack	*next;
}	t_stack;

// stacks (stack.c)
t_stack	*init_stack(char **nums, int count);
t_stack	*new_node(int val);
t_stack	*get_tail(t_stack *stack);
int		get_size(t_stack *stack);
void	print_stacks(t_stack *a, t_stack *b);

// operations (operations.c)
void	swap(t_stack **a, t_stack **b, char name);
void	push(t_stack **a, t_stack **b, char name);
void	rotate(t_stack **a, t_stack **b, int reverse, char name);

// utils (utils.c)
int		atoi_check(char *str, int *ptr);

// sorters (sorters.c)
void	radixlsd_sort(t_stack **a, t_stack **b);

// sorting utils (sorting_utils.c)
int		is_sorted(t_stack *stack);

#endif
