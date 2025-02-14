/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:17:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/11 18:25:27 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawers.h"

int	init_drawers(t_env *env)
{
	static t_dbuf	dbuf;
	t_encd			encoding;

	env->drawbuf = &dbuf;
	dbuf.mlximg = mlx_new_image(env->mlx, env->wsize_x, env->wsize_y);
	dbuf.data = (int *)mlx_get_data_addr(dbuf.mlximg,
			&encoding.bitspp, &encoding.line_size, &encoding.endian);
	dbuf.encoding = encoding;
	dbuf.sizex = env->wsize_x;
	dbuf.sizey = env->wsize_y;
	if (encoding.bitspp != sizeof(int) * 8 || encoding.endian)
		return (error(env, 1, "minilibx uses an unsupported encoding :("));
	return (0);
}

static void	draw_hmap_line(t_env *env, t_hmap *hmap, t_vec2 pos)
{
	t_hpt	hp1;
	t_hpt	hp2;
	t_vec2	sp1;
	t_vec2	sp2;

	hp1 = hmap_getpt(hmap, pos);
	sp1 = point2screen_iso(hmap, hp1.pos);
	if (pos.x < hmap->size.x - 1 != 0)
	{
		pos.x++;
		hp2 = hmap_getpt(hmap, pos);
		sp2 = point2screen_iso(hmap, hp2.pos);
		if (check_bounds(env, sp1) || check_bounds(env, sp2))
			draw_line(env, sp1, sp2, (t_grad){hp1.color, hp2.color});
		pos.x--;
	}
	if (pos.y < hmap->size.y - 1 != 0)
	{
		pos.y++;
		hp2 = hmap_getpt(hmap, pos);
		sp2 = point2screen_iso(hmap, hp2.pos);
		if (check_bounds(env, sp1) || check_bounds(env, sp2))
			draw_line(env, sp1, sp2, (t_grad){hp1.color, hp2.color});
	}
}

int	draw_hmap(t_env *env)
{
	const t_hmap	*hmap = env->hmap;
	t_vec2			cur;

	cur = (t_vec2){0, 0};
	ft_bzero(env->drawbuf->data,
		sizeof(int) * env->drawbuf->sizex * env->drawbuf->sizey);
	while (cur.x < hmap->size.x && cur.y < hmap->size.y)
	{
		draw_hmap_line(env, (t_hmap *)hmap, cur);
		cur.x++;
		if (cur.x >= hmap->size.x)
		{
			cur.x = 0;
			cur.y++;
		}
	}
	return (0);
}

int	draw_axes(t_env *env)
{
	t_vec2	origin;
	t_vec2	dir;

	origin = project_iso((t_vec3){0, 0, 0}, env->hmap->rot, env->hmap->offset);
	dir = project_iso((t_vec3){1000, 0, 0}, env->hmap->rot, env->hmap->offset);
	draw_line(env, origin, dir, (t_grad){int2clr(0xff0000), {.val = -1}});
	dir = project_iso((t_vec3){0, 1000, 0}, env->hmap->rot, env->hmap->offset);
	draw_line(env, origin, dir, (t_grad){int2clr(0x00ff00), {.val = -1}});
	dir = project_iso((t_vec3){0, 0, 1000}, env->hmap->rot, env->hmap->offset);
	draw_line(env, origin, dir, (t_grad){int2clr(0x0000ff), {.val = -1}});
	return (0);
}
