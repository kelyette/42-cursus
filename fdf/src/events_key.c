/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:14:36 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/14 13:04:29 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "hmap.h"

int	evf_key(int key, t_env *env)
{
	void	(**action)(t_env *, float, float, float);

	action = &env->ls->action;
	if (key == KEY_ESCAPE)
		fdfclose(env, 0);
	else if (key == KEY_TAB)
	{
		if (*action == &rotate)
			*action = &scale;
		else
			*action = &rotate;
	}
	else if (key == KEY_F && env->ls->redraw++)
		env->ls->showaxes ^= 1;
	else if (key == KEY_COMMA || key == KEY_DOT)
		env->ls->delta += ((key == KEY_DOT) * 2 - 1) * 0.5;
	else if (key == KEY_NUMPAD1)
		env->hmap->rot = (t_vec3){-0.734, 0.931, 1};
	if (env->ls->delta <= 0.2)
		env->ls->delta = 0.2;
	return (0);
}

int	evf_keyloop(t_env *env)
{
	t_ls	*ls;
	void	(*action)(t_env *env, float, float, float);

	ls = env->ls;
	if (!ls->anykey)
		return (0);
	action = ls->action;
	(*action)(env,
		get_complkey(ls->keybinds, KEY_LEFT, KEY_RIGHT),
		get_complkey(ls->keybinds, KEY_UP, KEY_DOWN),
		get_complkey(ls->keybinds, KEY_I, KEY_O));
	move(env,
		get_complkey(ls->keybinds, KEY_A, KEY_D),
		get_complkey(ls->keybinds, KEY_W, KEY_S),
		get_complkey(ls->keybinds, KEY_Q, KEY_E));
	return (0);
}

int	evf_keydown(int key, t_env *env)
{
	t_kbind	*keybind;

	ft_printf("%d\n", key);
	keybind = get_key(env->ls->keybinds, key);
	if (!keybind)
		return (0);
	env->ls->anykey++;
	keybind->state = -1;
	if (keybind->type == KBHold)
		keybind->state = 1;
	return (0);
}

int	evf_keyup(int key, t_env *env)
{
	t_kbind	*keybind;

	keybind = get_key(env->ls->keybinds, key);
	if (!keybind)
		return (0);
	env->ls->anykey--;
	if (keybind->type == KBOnce)
		evf_key(key, env);
	keybind->state = 0;
	return (0);
}
