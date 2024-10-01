/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:34:03 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/22 19:34:33 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*cs1;
	char	*cs2;

	cs1 = (char *)s1;
	cs2 = (char *)s2;
	i = -1;
	while (++i < n)
		if (cs1[i] != cs2[i])
			break ;
	return (cs1[i] - cs2[i]);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cs;
	size_t	i;

	cs = (char *)s;
	i = -1;
	while (++i < n)
		if (cs[i] == c)
			return (&cs[i]);
	return (NULL);
}
