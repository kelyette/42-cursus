/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 01:56:38 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 14:28:54 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	evf_mousemove(int x, int y, t_env *env)
{
	static t_vec2	lpos = {-1, -1};
	const t_vec2	delta = {lpos.x - x, lpos.y - y};

	if (env->ls->mouse == 1)
		rotate(env, delta.y * 0.1, 0, delta.x * 0.1); // TODO use hook
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
