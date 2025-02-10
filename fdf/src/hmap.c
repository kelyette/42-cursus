/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:59:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/04 16:02:45 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include <fcntl.h>

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
	hmap.pos = (t_vec3){0, 0, 0};
	hmap.origin_offset = vec3_mult(hmap.size, (t_vec3){0.5, 0.5, 0});
	hmap.rot = (t_vec3){0, 3.14, 0};
	hmap.scale = (t_vec3){40, 20, 5};
	hmap.offset = (t_vec2){635, 360};
	return (0);
}
