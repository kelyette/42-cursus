/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:55:18 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 13:30:22 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	rotate(t_env *env, float x, float y, float z)
{
	env->hmap->rot.x += -x * 0.05;
	env->hmap->rot.y += z * 0.05;
	env->hmap->rot.z += y * 0.05;
	env->ls->redraw = 1;
}

void	scale(t_env *env, float x, float y, float z)
{
	env->hmap->scale.x += x;
	env->hmap->scale.y += y;
	env->hmap->scale.z += z;
	env->ls->redraw = 1;
}

void	move(t_env *env, float x, float y, float z)
{
	env->hmap->pos.x += x * 0.1;
	env->hmap->pos.y += y * 0.1;
	env->hmap->pos.z += z * 0.1;
	env->ls->redraw = 1;
}
