/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:17:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/15 14:39:42 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawers.h"

int	init_drawers(t_env *env)
{
	static t_dbuf	dbuf;
	t_encd			encoding;

	env->drawbuf = &dbuf;
	dbuf.mlximg = mlx_new_image(env->mlx, env->wsize_x, env->wsize_y);
	dbuf.data = (int *)mlx_get_data_addr(env->mlx,
			&encoding.bitspp, &encoding.line_size, &encoding.endian);
	dbuf.encoding = encoding;
	if (encoding.bitspp != sizeof(int) * 8)
		return (error(env, 1, "unsupported encoding in mlx"));
	return (0);
}

static void	draw_hmap_line(t_env *env, t_hmap *hmap, t_vec2 pos)
{
	t_vec2	ps1;
	t_vec2	ps2;
	t_vec2	p2;

	ps1 = map2screen_iso(hmap, pos);
	if (pos.x < hmap->size.x - 1 != 0)
	{
		p2 = pos;
		p2.x += 1;
		ps2 = map2screen_iso(hmap, p2);
		draw_line(env, ps1, ps2, env->prefs.clr_hi);
	}
	if (pos.y < hmap->size.y - 1 != 0)
	{
		p2 = pos;
		p2.y += 1;
		ps2 = map2screen_iso(hmap, p2);
		draw_line(env, ps1, ps2, env->prefs.clr_hi);
	}
}

int	draw_hmap(t_env *env)
{
	const t_hmap	*hmap = env->hmap;
	t_vec2			cur;

	ft_bzero(&cur, sizeof(cur));
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
