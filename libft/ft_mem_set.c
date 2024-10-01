/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:32:57 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/22 19:33:40 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = 0;
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		((char *)b)[i] = c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (!count || !size)
	{
		size = 1;
		count = 1;
	}
	res = malloc(size * count);
	if (res)
		ft_bzero(res, size * count);
	return (res);
}
