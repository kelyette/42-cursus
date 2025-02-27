/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_primitives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 01:21:29 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/27 13:13:25 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawers.h"

inline int	check_bounds(t_env *env, t_vec2 p)
{
	return (p.x > 0.f && p.y > 0.f
		&& (int)p.x < env->drawbuf->sizex && (int)p.y < env->drawbuf->sizey);
}

int	draw_pixel(t_env *env, t_vec2 p, int color)
{
	t_dbuf	*dbuf;

	dbuf = env->drawbuf;
	if (check_bounds(env, p))
		dbuf->data[(int)p.x + (int)p.y * dbuf->sizex] = color;
	return (0);
}

int	draw_line(t_env *env, t_vec2 p1, t_vec2 p2, t_grad grad)
{
	float	dx;
	float	dy;
	float	s;
	float	ms;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (fabsf(dx) >= fabsf(dy))
		s = fabsf(dx);
	else
		s = fabsf(dy);
	dx /= s;
	dy /= s;
	ms = s;
	while (s > 0)
	{
		draw_pixel(env, p1, grad_lerp(grad, 1 - s / ms).val);
		p1.x += dx;
		p1.y += dy;
		s--;
	}
	return (0);
}
