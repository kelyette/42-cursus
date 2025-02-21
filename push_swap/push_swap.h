/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:04:00 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/21 00:06:01 by kcsajka          ###   ########.fr       */
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

// TODO remove in final
void	print_stacks(t_stack *a, t_stack *b);
void	print_stacks_bin(t_stack *a, t_stack *b);

// stacks (stacks.c)
t_stack	*init_stack(char **nums, int count);
int		add_node(t_stack **s, char *val);
t_stack	*get_tail(t_stack *stack);
int		get_size(t_stack *stack);
void	free_stack(t_stack *s);

// operations (operations.c)
void	swap(t_stack **a, t_stack **b, char name);
void	push(t_stack **a, t_stack **b, char name);
void	rotate(t_stack **a, t_stack **b, int reverse, char name);

// utils (utils.c)
int		atoi_check(char *str, int *ptr);
void	compress_stack(t_stack *s);
t_stack	*get_min(t_stack *s, t_stack *prev);
int		is_duplicate(t_stack *s, int val);
int		error_free(t_stack *s, char **split, int returnVal);

// sorters (sorters.c)
void	sort_3u(t_stack **a, int size);
void	sort_5u(t_stack **a, t_stack **b, int size);
void	radixlsd_sort(t_stacks *s);

// sorting utils (sorting_utils.c)
int		is_sorted(t_stack *stack, int rev);
int		get_msdi(t_stack *s);
int		get_min_dist(t_stack *a, t_stack *min[2], int dist[2]);
int		get_dist(t_stack *s, t_stack *trgt, int abs);

#endif
