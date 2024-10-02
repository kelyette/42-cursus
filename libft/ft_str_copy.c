/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:21:24 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/02 16:11:49 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	while (dstsize && src[++i] && i < dstsize - 1)
		dst[i] = src[i];
	if (dstsize)
		dst[i] = 0;
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] && i < dstsize - 1)
		i++;
	while (dstsize && *src && i < dstsize - 1)
		dst[i++] = *src++;
	if (dstsize)
		dst[i] = 0;
	return (dstsize + ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	res = malloc(ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}

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
