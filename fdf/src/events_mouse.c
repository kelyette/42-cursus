/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:56:38 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/27 14:49:14 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	evf_mousemove(int x, int y, t_env *env)
{
	static t_vec2	lpos = {-1, -1};
	const t_vec2	delta = {lpos.x - x, lpos.y - y};

	if (!env->ls->mouse)
	{
		lpos.x = -1;
		return (0);
	}
	if (lpos.x != -1)
	{
		if (env->ls->mouse == MOUSE1)
			rotate(env, delta.x * 0.1, 0, delta.y * 0.1);
		else if (env->ls->mouse == MOUSE2)
			move(env, -delta.x, -delta.y, 0);
	}
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
	if (btn == MOUSE_SUP)
		zoom(env, 1);
	else if (btn == MOUSE_SDOWN)
		zoom(env, -1);
	return (0);
}

int	evf_mouseup(int btn, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (env->ls->mouse == btn)
	{
		env->ls->mouse = 0;
		evf_mousemove(x, y, env);
	}
	return (0);
}
