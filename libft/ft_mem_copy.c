/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:31:13 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/02 15:05:17 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdst;

	csrc = (char *)src;
	cdst = (char *)dst;
	i = -1;
	while (++i < n)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == c)
			return (cdst);
	}
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cpy;
	char	*cdst;
	size_t	i;

	cdst = (char *)dst;
	cpy = malloc(len);
	ft_memcpy(cpy, src, len);
	i = -1;
	while (++i < len)
		cdst[i] = cpy[i];
	free(cpy);
	return (dst);
}
