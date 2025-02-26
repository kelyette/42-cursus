/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:57:39 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/26 13:58:34 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vec2	project_iso(t_vec3 v3, t_vec3 rot, t_vec2 offset)
{
	t_vec2	v2;

	v3 = vec3_rotate(v3, rot);
	v2.x = (-cos(0.5) * v3.x + cos(0.5) * v3.y) + offset.x;
	v2.y = (-cos(1) * v3.x + -cos(1) * v3.y + v3.z) + offset.y;
	return (v2);
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec3	vec3_subs(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3	vec3_mag(t_vec3 v, int f)
{
	v.x *= f;
	v.y *= f;
	v.z *= f;
	return (v);
}
