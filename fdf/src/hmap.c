/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:59:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/26 14:56:57 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include <fcntl.h>

static int	hmap_get_zsize(t_hpt *map, int size)
{
	float	min;
	float	max;
	int		i;

	min = 0;
	max = 0;
	i = -1;
	while (++i < size)
	{
		if (map[i].pos.z < min)
			min = map[i].pos.z;
		if (map[i].pos.z > max)
			max = map[i].pos.z;
	}
	return ((int)(max - min));
}

int	hmap_from_file(t_hmap *hmap, const char *path)
{
	int		fd;
	char	*line;
	int		sizex;
	int		sizey;
	int		i;

	if (get_hmap_size(path, &sizex, &sizey))
		return (1);
	hmap->map = ft_calloc(sizex * sizey, sizeof(t_hpt));
	if (!hmap->map || safe_open(&fd, path, O_RDONLY))
		return (1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_hmap_line(hmap->map + i * sizex, line, sizex, i))
			return (1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	hmap->size = (t_vec3){sizex, sizey, 0};
	return (0);
}

int	init_hmap(t_env *env, const char *path)
{
	static t_hmap	hmap;

	env->hmap = &hmap;
	if (hmap_from_file(&hmap, path))
		return (1);
	hmap.size.z = hmap_get_zsize(hmap.map, hmap.size.x * hmap.size.y);
	hmap.pos = (t_vec3){0, 0, 0};
	hmap.origin_offset = vec3_mult(hmap.size, (t_vec3){0.5, 0.5, 0});
	hmap.origin_offset = vec3_subs(hmap.origin_offset, (t_vec3){0.5, 0.5, 0.5});
	hmap.rot = (t_vec3){0, 3.14, 0};
	hmap.scale = (t_vec3){600 / hmap.size.x, 600 / hmap.size.x, 5};
	hmap.offset = (t_vec2){635, 360};
	return (0);
}
