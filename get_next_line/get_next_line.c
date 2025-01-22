/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:02:59 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/22 01:10:38 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*append_data(char *buffer, char *data)
{
	char	*new;
	int		len;
	int		dlen;

	if (!*data)
		return (0);
	dlen = ft_strlen(data);
	len = ft_strlen(buffer);
	new = ft_calloc(len + dlen + 1, 1);
	ft_memcpy(new, buffer, len);
	ft_memcpy(new + len, data, dlen);
	new[len + dlen] = 0;
	return (new);
}

int	read_next(int fd, char *buffer)
{
	char	rbuffer[BUFFER_SIZE];
	int		read_size;

	read_size = -1;
	while (!ft_strchr(rbuffer, '\n') || read_size)
	{
		read_size = read(fd, rbuffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buffer);
			return (1);
		}
		buffer = append_data(buffer, rbuffer);
	}
	return (0);
}

char	*get_line(char *buffer)
{
	char	*res;
	int		size;

	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	if (!buffer[size])
		return (buffer);
	res = ft_calloc(size, 1);
	ft_memcpy(res, buffer, size);
	return (res);
}

char	*shift_buffer(char *buffer)
{
	char	*nl_ptr;
	char	*new;
	int		newsize;

	nl_ptr = ft_strchr(buffer, '\n');
	if (!nl_ptr)
	{
		free(buffer);
		return (NULL);
	}
	if (nl_ptr == buffer)
		return (buffer);
	newsize = nl_ptr - buffer;
	new = ft_calloc(newsize, 1);
	ft_memcpy(new, buffer, ft_strlen(buffer) - newsize);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;

	read_apply()
}
