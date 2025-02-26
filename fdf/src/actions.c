/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:55:18 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/26 17:33:34 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

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
	(void)z;
	env->hmap->offset.x += x * 1 / env->ls->delta;
	env->hmap->offset.y += y * 1 / env->ls->delta;
	env->ls->redraw = 1;
}
