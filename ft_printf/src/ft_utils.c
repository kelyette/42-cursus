/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:21:06 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 02:45:13 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

long	max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

long	min(long a, long b)
{
	if (a < b)
		return (a);
	return (b);
}

char	hex_val(int n, int ucase)
{
	if (n < 0)
		return (0);
	if (n < 10)
		return (n + '0');
	if (n < 16)
		return (n - 10 + 'A' + (!ucase * 32));
	return (0);
}

size_t	get_length_base(long n, int base)
{
	size_t	size;

	size = !n;
	while (n != 0 && ++size)
		n /= base;
	return (size);
}
