/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:22:33 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/02 14:33:17 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

char	*apply_buffer(t_pbuf *pbuf, char *end_ptr)
{
	size_t	size;
	char	*line;

	size = end_ptr - (pbuf->buf + pbuf->start) + 1;
	if (size < 1)
		return (NULL);
	line = malloc(size + 1);
	ft_memcpy(line, pbuf->buf + pbuf->start, size);
	line[size] = 0;
	pbuf->start += size;
	return (line);
}

t_pbuf	*apply_new_data(t_pbuf *pbuf, const char *data, size_t size)
{
	pbuf->buf = ft_realloc(pbuf->buf, pbuf->end, pbuf->end + size);
	ft_memcpy(pbuf->buf + pbuf->end, data, size);
	pbuf->end += size;
	return (pbuf);
}

char	*get_next_line(int fd)
{
	static t_pbuf	pbuf;
	char			buf[BUFFER_SIZE];
	char			*line;
	char			*nl_ptr;
	size_t			read_size;

	while (1)
	{
		nl_ptr = ft_memchr(pbuf.buf + pbuf.start, '\n', pbuf.end - pbuf.start);
		if (nl_ptr)
			return (apply_buffer(&pbuf, nl_ptr));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == 0)
		{
			line = apply_buffer(&pbuf, pbuf.buf + pbuf.end - 1);
			if (pbuf.buf)
			{
				free(pbuf.buf);
				pbuf.buf = NULL;
			}
			return (NULL);
		}
		apply_new_data(&pbuf, buf, read_size);
	}
}
