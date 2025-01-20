/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:22:07 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/15 23:50:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "hmap.h"

t_vec3	hmap_getpt(t_hmap *hmap, t_vec2 pos)
{
	t_vec3			r;

	//printf("getpt: %d, %d\nsize: %.1f, %.1f\n", (int)pos.x, (int)pos.y, hmap->size.x, hmap->size.y);
	if (!hmap->map)
		return ((t_vec3){0});
	if (pos.x > hmap->size.x || pos.y > hmap->size.y)
		return ((t_vec3){0});
	r.x = pos.x;
	r.y = pos.y;
	r.z = hmap->map[(int)(pos.y * hmap->size.x + pos.x)];
	r = vec3_subs(r, vec3_mult(hmap->size, hmap->origin));
	r = vec3_mult(r, hmap->scale);
	r = vec3_add(r, hmap->pos);
	return (r);
}

t_vec2	map2screen_iso(t_hmap *hmap, t_vec2 pos)
{
	t_vec3	world_pt;
	t_vec2	screen_pt;

	world_pt = hmap_getpt(hmap, pos);
	screen_pt = vec3to2_iso(world_pt, hmap->rot, hmap->offset);
	screen_pt.x += hmap->pos.x;
	screen_pt.y += hmap->pos.y;
	return (screen_pt);
}

int	safe_open(int *fd, const char *path, int oflag)
{
	*fd = open(path, oflag);
	if (*fd != -1)
		return (0);
	ft_printf("fdf: cannot open file \"%s\" (error %d)\n", path, errno);
	return (1);
}

void	print_hmap(t_pt *map, t_vec2 size)
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
			ft_printf("%-3d", map[x + y * sizex]);
		ft_printf("\n");
	}
	ft_printf("size: %d, %d\n", sizex, sizey);
}
