/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:56:38 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/19 03:40:12 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include<stdio.h>

int	evf_mouse(int btn, int x, int y, t_env *env)
{
	static t_vec2	lpos = {-1, -1};

	if (btn || 1)
		return (0);
	if (lpos.x == -1)
	{
		lpos.x = x;
		lpos.y = y;
		return (0);
	}
	draw_line(env, lpos, (t_vec2){x, y});
	lpos.x = x;
	lpos.y = y;
	return (0);
}

int	evf_mousemove(int x, int y, t_env *env)
{
	static t_vec2	lpos = {-1, -1};
	const t_vec2	delta = {lpos.x - x, lpos.y - y};

	if (env->ls->mouse == 1)
		rotate(env, delta.y * 0.1, 0, delta.x * 0.1);
	lpos = (t_vec2){x, y};
	return (0);
}

int	evf_mousedown(int btn, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (env->ls->mouse)
		return (0);
	env->ls->mouse = btn;
	return (0);
}

int	evf_mouseup(int btn, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (env->ls->mouse == btn)
		env->ls->mouse = 0;
	return (0);
}
