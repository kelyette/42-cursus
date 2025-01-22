/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:43:44 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/22 15:20:03 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	s;

	s = 0;
	while (str[s])
		s++;
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (char)c)
			return ((char *)--s);
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = -1;
	while (++i < n)
		((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}

void	ft_bzero(void *d, size_t n)
{
	while (n--)
		*(char *)d++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void		*res;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	res = malloc(size * count);
	if (!res)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}
