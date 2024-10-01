/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:22:33 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/30 19:31:25 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#include <stdio.h>

size_t	ft_strcpy(char *dst, char *src)
{
	size_t	size;

	if (!dst || !src)
		return (0);
	size = 0;
	while (*src && ++size)
		*dst++ = *src++;
	*dst = 0;
	return (size);
}

size_t	strccpy(char *base, char *str, char c, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
	{
		base[i] = str[i];
		if (str[i] == c)
		{
			printf("reached c (%c)\n", str[i - 1]);
			base[++i] = 0;
			return (1);
		}
	}
	return (0);
}

#include <stdio.h>

int	resize_cat(char **base, char *str, size_t bsize, size_t size)
{
	int		r;
	char	*res;

	res = malloc(bsize + size + 1);
	if (base)
		ft_strcpy(res, *base);
	r = (strccpy(res + bsize, str, '\n', size));
	printf("%-4d%.*s\n", r, (int)(bsize + size + 1), res);
	*base = res;
	return (r);
}

char	*get_next_line(int fd)
{
	char	*res;
	char	*buffer;
	ssize_t	read_size;
	size_t	rsize;
	int		any;

	rsize = 0;
	res = 0;
	buffer = malloc(BUFFER_SIZE);
	any = 0;
	read_size = 1;
	while (read_size)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size)
		{
			any = 1;
			if (resize_cat(&res, buffer, rsize, read_size))
				break ;
			rsize += read_size;
		}
	}
	if (!any)
		return (NULL);
	printf("res %s ser\n", res);
	return (res);
}
