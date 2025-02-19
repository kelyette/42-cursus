/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:00 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/19 13:29:00 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include "libft.h"

typedef struct s_stack
{
	int				val;
	int				baseval;
	struct s_stack	*next;
}	t_stack;

typedef struct s_stacks
{
	t_stack	*a;
	t_stack	*b;
}	t_stacks;

// stacks (stack.c)
t_stack	*init_stack(char **nums, int count);
int		add_node(t_stack **s, char *val);
t_stack	*get_tail(t_stack *stack);
int		get_size(t_stack *stack);
void	compress_stack(t_stack *s);
void	print_stacks(t_stack *a, t_stack *b);
void	print_stacks_bin(t_stack *a, t_stack *b);

// operations (operations.c)
void	swap(t_stack **a, t_stack **b, char name);
void	push(t_stack **a, t_stack **b, char name);
void	rotate(t_stack **a, t_stack **b, int reverse, char name);

// utils (utils.c)
int		atoi_check(char *str, int *ptr);
int		is_duplicate(t_stack *s, int val);

// sorters (sorters.c)
void	sort_3u(t_stack **a);
void	sort_5u(t_stack **a, t_stack **b);
void	radixlsd_sort(t_stacks *s);

// sorting utils (sorting_utils.c)
int		is_sorted(t_stack *stack, int rev);
int		get_msdi(t_stack *s);
t_stack	*get_nth(t_stack *s, int n);

#endif
