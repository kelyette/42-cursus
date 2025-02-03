/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:47:00 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 20:03:39 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include <unistd.h>
#include <fcntl.h>

int	ctoi(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= '0' && c <= '9')
		return (c - '0');
	return (-1);
}

int	stroi(char *str, char **end_ptr)
{
	int		res;
	int		sign;
	int		base;

	res = 0;
	sign = 1;
	base = 10;
	while (*str == ' ')
		str++;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		base = 16;
		str += 2;
	}
	else if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ctoi(*str) != -1)
		res = res * base + ctoi(*str++);
	if (end_ptr)
		*end_ptr = str;
	return (res * sign);
}

int	get_hmap_size(const char *path, int *xptr, int *yptr)
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

int	parse_hpt(t_hpt *hpt, char *line)
{
	char	**parts;
	char	*end;

	parts = ft_split(line, ',');
	hpt->pos.z = stroi(parts[0], &end);
	if (line == end || (*end != ' ' && *end != '\n' && *end))
		return (free_split(parts));
	if (parts[1])
	{
		hpt->color = int2clr(stroi(parts[1], &end));
		if (line == end || (*end != ' ' && *end != '\n' && *end) || parts[2])
			return (free_split(parts));
	}
	else
		hpt->color = int2clr(0x8000ff);
	free_split(parts);
	return (0);
}

int	parse_hmap_line(t_hpt *map, const char *line, int xlen, int ypos)
{
	char	**parts;
	int		i;

	parts = ft_split(line, ' ');
	i = -1;
	while (parts && ++i < xlen)
	{
		map->pos = (t_vec3){i, ypos, 0};
		if (parse_hpt(map++, parts[i]))
		{
			free_split(parts);
			ft_printf("fdf: error: parse error near \"%s\"\n", parts[i]);
			exit(1);
		}
	}
	if (i != xlen)
	{
		ft_printf("fdf: error: line length mismatch in map file"
			" (near \"%.10s...\")\n", line);
		free_split(parts);
		exit(1);
	}
	free_split(parts);
	return (0);
}
