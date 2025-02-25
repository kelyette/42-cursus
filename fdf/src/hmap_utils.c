/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:22:07 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/25 17:27:53 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "hmap.h"

int	free_split(char **split)
{
	char	**tmp;

	tmp = split;
	while (*split)
		free(*split++);
	free(tmp);
	return (1);
}

t_hpt	hmap_getpt(t_hmap *hmap, t_vec2 pos)
{
	t_hpt	r;

	if (!hmap->map)
		return ((t_hpt){0});
	if (pos.x > hmap->size.x || pos.y > hmap->size.y)
		return ((t_hpt){0});
	r = hmap->map[(int)(pos.y * hmap->size.x + pos.x)];
	r.pos = vec3_subs(r.pos, hmap->origin_offset);
	r.pos = vec3_mult(r.pos, hmap->scale);
	r.pos = vec3_add(r.pos, hmap->pos);
	return (r);
}

t_vec2	point2screen_iso(t_hmap *hmap, t_vec3 p)
{
	t_vec2	sp;

	sp = project_iso(p, hmap->rot, hmap->offset);
	sp.x += hmap->pos.x;
	sp.y += hmap->pos.y;
	return (sp);
}

int	safe_open(int *fd, const char *path, int oflag)
{
	*fd = open(path, oflag);
	if (*fd != -1 && read(*fd, 0, 0) != -1)
		return (0);
	ft_printf("fdf: cannot open file \"%s\" (error %d)\n", path, errno);
	return (1);
}

void	print_hmap(t_hpt *map, t_vec2 size)
{
	int			x;
	int			y;
	const int	sizex = size.x;
	const int	sizey = size.y;

	y = -1;
	while (++y < sizey)
	{
		x = -1;
		while (++x < sizex)
			ft_printf("%-3d", (int)map[x + y * sizex].pos.z);
		ft_printf("\n");
	}
	ft_printf("size: %d, %d\n", sizex, sizey);
}
