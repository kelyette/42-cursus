/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 01:21:29 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/26 20:26:24 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawers.h"

int	draw_pixel(t_env *env, int buffered, t_vec2 p, int color)
{
	t_dbuf	*dbuf;

	if (!buffered)
	{
		mlx_pixel_put(env->mlx, env->win, p.x, p.y, color);
		return (0);
	}
	dbuf = env->drawbuf;
	dbuf->img->data[(int)(p.x + p.y * dbuf->rect.size.x)] = color;
	return (0);
}

int	draw_line(t_env *env, t_vec2 p1, t_vec2 p2, int color)
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
			color);
		p1.x += dx;
		p1.y += dy;
	}
	return (0);
}

int	draw_rect(t_env *env, t_rect rect, int color)
{
	t_vec2	cur;

	ft_bzero(&cur, sizeof(t_vec2));
	while (cur.x < rect.size.x)
		while (cur.y < rect.size.y)
			draw_pixel(env, 0, cur, color);
	return (0);
}
