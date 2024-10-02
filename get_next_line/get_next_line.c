/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:22:33 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/01 19:43:17 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t size)
{
	char	*cs = (char *)s;
	size_t	i;

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
	size_t		si;

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

char	*get_next_line(int fd)
{
	static char		*prevbuf;
	static size_t	pbstart;
	static size_t	pbend;
	char			buf[BUFFER_SIZE];
	char			*line;
	char			*nl_ptr;
	size_t			read_size;
	size_t			line_size;

	while (1)
	{
		nl_ptr = ft_memchr(prevbuf + pbstart, '\n', pbend - pbstart);
		if (nl_ptr)
		{
			// copy prevbuf into line buffer and return
			line_size = nl_ptr - (prevbuf + pbstart) + 1;
			line = malloc(line_size + 1);
			ft_memcpy(line, prevbuf + pbstart, line_size);
			line[line_size] = 0;
			pbstart += line_size;
			return (line);
		}

		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
		{
			line_size = pbstart + read_size;
			line = malloc(line_size + 1);
			ft_memcpy(line, prevbuf + pbstart, line_size);
			line[line_size] = 0;
			pbstart = 0;
			pbend = 0;
			if (prevbuf)
				free(prevbuf);
			// eof, same as last if statement except free and reset static vars
			return (NULL);
		}

		// make room for prevbuf and copy new data
		prevbuf = ft_realloc(prevbuf, pbend, pbend + read_size);
		ft_memcpy(prevbuf + pbend, buf, read_size);
		pbend += read_size;
	}
}
