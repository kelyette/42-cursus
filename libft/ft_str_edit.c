/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:23:50 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/08 14:09:29 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*res;
	size_t	len;
	size_t	start;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	len = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[len]))
		len--;
	len -= start;
	res = ft_substr(s1, start, len + 1);
	if (!res)
		return (NULL);
	return (res);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = malloc(size);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}

char	**ft_split(const char *s, char c)
{
	char const	*cs = (char *)s;
	char		**res;
	int			scount;
	size_t		slen;

	if (!s)
		return (NULL);
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

	if (!s || !f)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = (*f)(i, s[i]);
	res[i] = 0;
	return (res);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = -1;
	while (s[++i])
		(*f)(i, &s[i]);
	return ;
}
