/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:50 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/22 19:24:44 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*res;
	size_t	size;
	size_t	i;

	i = -1;
	size = 0;
	while (s1[++i])
		if (!ft_strchr(set, s1[i]))
			size++;
	res = malloc(size + 1);
	i = 0;
	while (*s1)
	{
		if (!ft_strchr(set, *s1))
			res[i++] = *s1;
		s1++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(size);
	ft_strlcpy(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	char	*cs;
	int		scount;
	size_t	slen;

	cs = (char *)s;
	scount = 0;
	while (*s)
		if (*s++ != c && (!*s || *s == c))
			scount++;
	res = malloc(sizeof(char *) * (scount + 1));
	if (!res)
		return (NULL);
	while (cs - s < 0)
	{
		slen = 0;
		while (cs[slen] && cs[slen] != c)
			slen++;
		if (slen > 0)
			*res++ = ft_strndup(cs, slen);
		cs += slen + 1;
	}
	*res = NULL;
	return (res - scount);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = (*f)(i, s[i]);
	res[i] = 0;
	return (res);
}
