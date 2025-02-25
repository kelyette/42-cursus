/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:24:47 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/25 17:24:58 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "events.h"
#include "drawers.h"

void	init_keybinds(t_kbind *keybinds)
{
	int	i;

	i = 0;
	keybinds[i++] = (t_kbind){KEY_W, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_A, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_S, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_D, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_Q, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_E, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_I, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_O, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_LEFT, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_RIGHT, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_DOWN, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_UP, KBHold, 0};
	keybinds[i++] = (t_kbind){KEY_F, KBOnce, 0};
	keybinds[i++] = (t_kbind){KEY_TAB, KBOnce, 0};
	keybinds[i++] = (t_kbind){KEY_ESCAPE, KBOnce, 0};
	keybinds[i++] = (t_kbind){KEY_COMMA, KBOnce, 0};
	keybinds[i++] = (t_kbind){KEY_DOT, KBOnce, 0};
	keybinds[i] = (t_kbind){-1, -1, -1};
}

int	init_hooks(t_env *env)
{
	mlx_hook(env->win, ON_KEYDOWN, (1L << 0), &evf_keydown, env);
	mlx_hook(env->win, ON_KEYUP, (1L << 1), &evf_keyup, env);
	mlx_hook(env->win, ON_MOUSEDOWN, (1L << 2), &evf_mousedown, env);
	mlx_hook(env->win, ON_MOUSEUP, (1L << 3), &evf_mouseup, env);
	mlx_hook(env->win, ON_MOUSEMOVE, (1L << 13), &evf_mousemove, env);
	mlx_hook(env->win, ON_DESTROY, 1, &fdfclose, env);
	mlx_loop_hook(env->mlx, &evf_loop, env);
	return (0);
}

int	init_loop(t_env *env)
{
	static t_ls	ls;

	env->ls = &ls;
	ls.delta = 1;
	ls.action = &rotate;
	init_keybinds(ls.keybinds);
	init_info(env);
	return (0);
}

int	evf_loop(t_env *env)
{
	t_ls	*ls;

	ls = env->ls;
	if (ls->i == 0 || ls->redraw)
	{
		ls->redraw = 0;
		draw_hmap(env);
		if (ls->showaxes)
			draw_axes(env);
		mlx_put_image_to_window(env->mlx, env->win, env->drawbuf->mlximg, 0, 0);
		draw_info(env);
	}
	evf_keyloop(env);
	ls->i++;
	if (ls->i >= INT_MAX)
		ls->i = 0;
	return (0);
}
