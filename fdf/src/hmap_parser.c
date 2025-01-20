/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:47:00 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/16 19:42:02 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include <unistd.h>
#include <fcntl.h>

int	parse_xlength(const char *path, int *xptr, int *yptr)
{
	int		fd;
	char	*line;

	*xptr = 0;
	*yptr = 0;
	if (safe_open(&fd, path, O_RDONLY))
		return (1);
	line = get_next_line(fd);
	while (*line)
	{
		if (ft_isdigit(*line) && ++*xptr)
			while (ft_isdigit(*line))
				line++;
		else
			line++;
	}
	while (line && ++*yptr)
		line = get_next_line(fd);
	close(fd);
	return (0);
}

int	parse_hmap_pt(t_pt *pt, const char **lineptr)
{
	char	*line;

	line = (char *)*lineptr;
	while (ft_isdigit(*line))
	{

	}
	return (i);
}

int	parse_hmap_line(t_pt **mapptr, const char *line, int xlen)
{
	t_pt	*map;
	t_vec3	pos;

	map = *mapptr;
	while (*line != '\n' && *line && xlen > 0)
	{
		pos = (t_vec3){0, 0, 0};
		if (ft_isdigit(*line))
			pos.z = 10 * pos.z + (*line++ - '0');
		else if (*line == ' ')
		{
			map->pos = pos;
			xlen--;
			map++;
			while (*line == ' ')
				line++;
		}
		else if (*line != '\n')
		{
			ft_printf(
				"fdf: error: unexpected character '%c' (%d)", *line, *line);
			return (1);
		}
	}
	*mapptr = ++map;
	return (0);
}
