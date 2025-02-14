/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:55:18 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/14 12:33:02 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	fdfclose(t_env *env, int code)
{
	if (env && env->mlx && env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env && env->hmap->map)
		free(env->hmap->map);
	if (env && env->ls->info)
		free_info(env->ls->info, env->ls->info_count);
	exit(code);
	return (0);
}

void	rotate(t_env *env, float x, float y, float z)
{
	env->hmap->rot.x += -x * (0.05 / env->ls->delta);
	env->hmap->rot.y += z * (0.05 / env->ls->delta);
	env->hmap->rot.z += y * (0.05 / env->ls->delta);
	env->ls->redraw = 1;
}

void	scale(t_env *env, float x, float y, float z)
{
	env->hmap->scale.x += x * 0.2 / env->ls->delta;
	env->hmap->scale.y += y * 0.2 / env->ls->delta;
	env->hmap->scale.z += z * 0.2 / env->ls->delta;
	env->ls->redraw = 1;
}

void	move(t_env *env, float x, float y, float z)
{
	env->hmap->pos.x += x * 0.1 / env->ls->delta;
	env->hmap->pos.y += y * 0.1 / env->ls->delta;
	env->hmap->pos.z += z * 0.1 / env->ls->delta;
	env->ls->redraw = 1;
}
