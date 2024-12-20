/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:17:05 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/16 16:37:48 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	free_pbuf(t_pbuf *pbuf)
{
	if (!pbuf->buf)
		return (1);
	free(pbuf->buf);
	pbuf->buf = NULL;
	pbuf->start = 0;
	pbuf->end = 0;
	return (1);
}

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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;

	if (!dst && !src)
		return (NULL);
	cdst = (char *)dst;
	csrc = (char *)src;
	if (dst <= src)
		while (len--)
			*cdst++ = *csrc++;
	else
	{
		cdst += len -1;
		csrc += len -1;
		while (len--)
			*cdst-- = *csrc--;
	}
	return (dst);
}
