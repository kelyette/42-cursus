/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:17:57 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/20 17:08:56 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawers.h"

int	init_drawers(t_env *env)
{
	t_dbuf	*drawbuf;

	drawbuf = env->drawbuf;
	drawbuf->img = mlx_new_image(env->mlx, 1270, 720);
	drawbuf->
	return (0);
}

int	draw_line(t_env *env, t_vec2 p1, t_vec2 p2)
{
	float	dx;
	float	dy;
	float	s;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabsf(dx) >= fabsf(dy))
		s = fabsf(dx);
	else
		s = fabsf(dy);
	dx /= s;
	dy /= s;
	while (s-- > 0)
	{
		mlx_pixel_put(
			env->mlx, env->win,
			(int)round(p1.x), (int)round(p1.y),
			env->prefs.clr_hi);
		p1.x += dx;
		p1.y += dy;
	}
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
		draw_line(env, ps1, ps2);
	}
	if (pos.y < hmap->size.y - 1 != 0)
	{
		p2 = pos;
		p2.y += 1;
		ps2 = map2screen_iso(hmap, p2);
		draw_line(env, ps1, ps2);
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
