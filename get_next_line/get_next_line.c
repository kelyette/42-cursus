/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:02:59 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/25 12:05:01 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*append_data(char *buffer, char *data)
{
	char	*new;
	int		len;
	int		dlen;

	if (!data || !*data || !buffer)
		return (NULL);
	dlen = ft_strlen(data);
	len = ft_strlen(buffer);
	new = ft_calloc(len + dlen + 1, 1);
	if (!new)
		return (NULL);
	if (len)
		ft_memcpy(new, buffer, len);
	ft_memcpy(new + len, data, dlen);
	new[len + dlen] = 0;
	free(buffer);
	return (new);
}

int	read_next(int fd, char **bufptr)
{
	char	rbuffer[BUFFER_SIZE + 2];
	char	*buffer;
	int		read_size;
	char	*nlptr;

	buffer = *bufptr;
	if (!*bufptr)
		buffer = ft_calloc(1, 1);
	read_size = -1;
	while (read_size)
	if (!buffer)
		return (0);
	read_size = -1;
	while (!ft_strchr(buffer, '\n') && read_size)
	{
		read_size = read(fd, rbuffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buffer);
			return (1);
		}
		if (!read_size)
			break ;
		rbuffer[read_size] = 0;
		buffer = append_data(buffer, rbuffer);
		nlptr = ft_strchr(buffer, '\n');
		if (!(read_size && nlptr && ft_strlen(nlptr) > 1))
			break ;
	}
	*bufptr = buffer;
	return (0);
}

char	*get_res(char *buffer)
{
	char	*res;
	int		size;

	if (!*buffer)
		return (NULL);
	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	res = ft_calloc(size + !!buffer[size] + 1, 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, buffer, size);
	if (buffer[size])
		res[size] = '\n';
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
	nl_ptr++;
	newsize = ft_strlen(nl_ptr);
	new = ft_calloc(newsize + 1, 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, nl_ptr, newsize);
	new[newsize] = 0;
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;

	if (fd == -1)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	if (read_next(fd, &buffer) || !buffer)
		return (NULL);
	res = get_res(buffer);
	buffer = shift_buffer(buffer);
	return (res);
}
