/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:14:44 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/13 12:40:53 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#define VIEW_FOV 130

t_vec2	project_iso(t_vec3 v3, t_vec3 rot, t_vec2 offset)
{
	t_vec2	v2;

	v3 = vec3_rotate(v3, rot);
	v2.x = (-cos(0.5) * v3.x + cos(0.5) * v3.y) + offset.x;
	v2.y = (-cos(1) * v3.x + -cos(1) * v3.y + v3.z) + offset.y;
	return (v2);
}

t_vec2	project_perspective(t_vec3 v3, t_vec3 rot, t_vec2 offset)
{
	t_vec2	v2;

	v3 = vec3_add(v3, (t_vec3){100, 100, 100});
	v3 = vec3_rotate(v3, rot);
	if (v3.z == 0)
		v3.z = 0.0001f;
	v2.x = (VIEW_FOV * v3.x) / v3.z + offset.x;
	v2.y = (VIEW_FOV * v3.y) / v3.z + offset.y;
	return (v2);
}
