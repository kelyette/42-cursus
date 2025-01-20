/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:14:36 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/28 22:53:46 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "hmap.h"
#include<stdio.h>

int	evf_key(int key, t_env *env)
{
	void	(**action)(t_env *, float, float, float);

	printf("KEYPRESSED %d\n", key);
	action = &env->ls->action;
	if (key == KEY_ESCAPE)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	if (key == KEY_TAB)
	{
		if (*action == &rotate)
			*action = &scale;
		else
			*action = &rotate;
		printf("action is now %s", *action == &scale ? "&scale" : "&rotate");
	}
	return (0);
}

int	evf_keyloop(t_env *env)
{
	t_ls	*ls;
	void	(*action)(t_env *env, float, float, float);

	ls = env->ls;
	if (!ls->anykey)
		return (0);
	//printf("%d | KEYHELD!!! %d\n", ls->i % 10, ls->anykey);
	action = ls->action;
	(*action)(env,
		get_complkey(ls->keybinds, KEY_LEFT, KEY_RIGHT),
		get_complkey(ls->keybinds, KEY_UP, KEY_DOWN),
		get_complkey(ls->keybinds, KEY_I, KEY_O));
	return (0);
}

int	evf_keydown(int key, t_env *env)
{
	t_kbind	*keybind;

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
	printf("KEYUP!!! %d\n", env->ls->anykey);
	return (0);
}
