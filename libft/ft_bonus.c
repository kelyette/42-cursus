/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:33:50 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/07 16:34:42 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	i;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < n && s1[i])
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

size_t	ft_max_sizet(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}
