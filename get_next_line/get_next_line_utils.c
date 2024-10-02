/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:22:34 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/02 12:51:44 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	size;

	if (!s)
		return (0);
	size = 0;
	while (*s++)
		size++;
	return (size);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;
	size_t	i;

	if (!count || !size)
	{
		size = 1;
		count = 1;
	}
	res = malloc(size * count);
	i = -1;
	while (++i < size * count)
		res[i] = 0;
	return ((void *)res);
}

void	*ft_memchr(const void *s, int c, size_t size)
{
	const char	*cs = (char *)s;
	size_t		i;

	i = -1;
	while (++i < size)
		if (cs[i] == c)
			return ((void *)&s[i]);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	char	*cdst;
	char	*csrc;
	size_t	si;

	cdst = (char *)dst;
	csrc = (char *)src;
	si = -1;
	while (++si < size)
		cdst[si] = csrc[si];
	return (dst);
}

void	*ft_realloc(void *s, size_t bsize, size_t nsize)
{
	char		*res;

	res = malloc(nsize);
	ft_memcpy(res, s, bsize);
	if (s)
		free(s);
	return (res);
}
