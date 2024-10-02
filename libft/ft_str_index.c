/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:25:07 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/02 15:57:34 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	i;

	i = -1;
	while (s[++i])
		if (ft_strchr(charset, s[i]))
			break ;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ih;
	size_t	in;

	ih = -1;
	while (haystack[++ih] && ih < len)
	{
		in = 0;
		while (haystack[ih + in] == needle[in])
		{
			in++;
			if (!needle[in])
				return ((char *)&haystack[ih]);
		}
	}
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	s += start;
	i = -1;
	while (++i < len)
		*res++ = s[i];
	*res = 0;
	return (res - len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
		if (*s++ == (char)c)
			return ((char *)--s);
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	if (!s)
		return (NULL);
	p = NULL;
	while (*s)
	{
		if (*s == (char)c)
			p = (char *)s;
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (p);
}
