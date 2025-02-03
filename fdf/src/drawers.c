/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:17:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 19:47:29 by kcsajka          ###   ########.fr       */
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
		pos.x += 1;
		hp2 = hmap_getpt(hmap, pos);
		sp2 = point2screen_iso(hmap, hp2.pos);
		draw_line(env, sp1, sp2, (t_grad){hp1.color, hp2.color});
		pos.x -= 1;
	}
	if (pos.y < hmap->size.y - 1 != 0)
	{
		pos.y += 1;
		hp2 = hmap_getpt(hmap, pos);
		sp2 = point2screen_iso(hmap, hp2.pos);
		draw_line(env, sp1, sp2, (t_grad){hp1.color, hp2.color});
	}
}

int	draw_hmap(t_env *env)
{
	const t_hmap	*hmap = env->hmap;
	t_vec2			cur;

	cur = (t_vec2){0, 0};
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
	(void)env;
	return (0);
}
