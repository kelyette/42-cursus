/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:10:23 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/20 16:59:35 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_all(t_pbuf *pbufs)
{
	int	i;

	i = -1;
	while (++i < FILE_MAX)
	{
		free_pbuf(pbufs++);
	}
}

char	*apply_buffer(t_pbuf *pbuf, char *end_ptr, int dofree)
{
	size_t	size;
	char	*line;

	size = end_ptr - (pbuf->buf + pbuf->start) + 1;
	if (size < 1 && dofree)
		free_pbuf(pbuf);
	if (size < 1)
		return (NULL);
	line = malloc(size + 1);
	if (!line && free_pbuf(pbuf))
		return (NULL);
	ft_memcpy(line, pbuf->buf + pbuf->start, size);
	line[size] = 0;
	pbuf->start += size;
	if (dofree)
		free_pbuf(pbuf);
	return (line);
}

int	apply_new_data(t_pbuf *pbuf, const char *data, size_t size)
{
	char		*tmp;
	const int	pbufsize = pbuf->end - pbuf->start;

	tmp = malloc(pbufsize + size);
	if (!tmp && free_pbuf(pbuf))
		return (1);
	if (pbufsize > 0)
		ft_memcpy(tmp, pbuf->buf + pbuf->start, pbuf->end - pbuf->start);
	ft_memcpy(tmp + pbufsize, data, size);
	free(pbuf->buf);
	pbuf->buf = tmp;
	pbuf->start = 0;
	pbuf->end = pbufsize + size;
	return (0);
}

static int	handle_read_size(int rs, t_pbuf *pbuf)
{
	if (rs == 0 && !pbuf->buf)
		return (1);
	if (rs != -1)
		return (0);
	free_pbuf(pbuf);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_pbuf	pbufs[FILE_MAX];
	char			buf[BUFFER_SIZE];
	char			*nl_ptr;
	ssize_t			read_size;

	if (fd == -1 || fd > FILE_MAX)
		return (NULL);
	while (1)
	{
		nl_ptr = ft_memchr(pbufs[fd].buf + pbufs[fd].start, '\n',
				pbufs[fd].end - pbufs[fd].start);
		if (nl_ptr)
			return (apply_buffer(&pbufs[fd], nl_ptr, 0));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (handle_read_size(read_size, &pbufs[fd]))
			return (NULL);
		if (read_size == 0)
			return (apply_buffer(&pbufs[fd],
					pbufs[fd].buf + pbufs[fd].end - 1, 1));
		if (apply_new_data(&pbufs[fd], buf, read_size))
			return (NULL);
	}
}
