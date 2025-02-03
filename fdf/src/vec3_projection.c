/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:14:44 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 15:20:19 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vec2	project_iso(t_vec3 v3, t_vec3 rot, t_vec2 offset)
{
	t_vec2			v2;

	v3 = vec3_rotate(v3, rot);
	v2.x = (-cos(0.5) * v3.x + cos(0.5) * v3.y) + offset.x;
	v2.y = (-cos(1) * v3.x + -cos(1) * v3.y + v3.z) + offset.y;
	return (v2);
}

// TODO
// t_vec2 project_perspective(t_vec3 v3, t_vec3 rot, t_vec2 offset)
