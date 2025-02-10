/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:27:55 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/05 20:21:58 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' '
			&& ft_printf("error: unexpected character '%c'\n", *str))
			return (1);
		res = res * 10 + (*str++ - '0');
	}
	*ptr *= res;
	return (0);
}
