/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:59:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/16 16:29:27 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"
#include <fcntl.h>
#include<stdio.h>

int	hmap_from_file(t_hmap *hmap, const char *path)
{
	int		fd;
	char	*line;
	t_pt	*map;
	int		sizex;
	int		sizey;

	if (parse_xlength(path, &sizex, &sizey))
		return (1);
	map = ft_calloc(sizex * sizey, sizeof(t_pt));
	hmap->map = map;
	printf("before\n");
	print_hmap(map, (t_vec2){sizex, sizey});
	printf("---------------\n");
	if (!map || safe_open(&fd, path, O_RDONLY))
		return (1);
	printf("hmap size: %d by %d\n", sizex, sizey);
	line = get_next_line(fd);
	while (line)
	{
		if (parse_hmap_line(&map, line, sizex))
			return (1);
		line = get_next_line(fd);
	}
	hmap->size = (t_vec3){sizex, sizey, 0};
	print_hmap(hmap->map, (t_vec2){sizex, sizey});
	printf("done hmap (%d, %d)\n", sizex, sizey);
	return (0);
}

int	init_hmap(t_env *env, const char *path)
{
	static t_hmap	hmap;

	env->hmap = &hmap;
	if (hmap_from_file(&hmap, path))
		return (1);
	hmap.scale = (t_vec3){40, 20, 5};
	hmap.pos = (t_vec3){0, 0, 0};
	hmap.origin = (t_vec3){0.5, 0.5, 0};
	hmap.offset = (t_vec2){635, 360};
	return (0);
}
