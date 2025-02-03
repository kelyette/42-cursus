/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 03:31:15 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 15:14:18 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vec3	vec3_rotate(t_vec3 p, t_vec3 rot)
{
	p = vec3_rotatez(p, rot.z);
	p = vec3_rotatey(p, rot.y);
	p = vec3_rotatex(p, rot.x);
	return (p);
}

t_vec3	vec3_rotatex(t_vec3 p, float alpha)
{
	const float	sin_a = sin(alpha);
	const float	cos_a = cos(alpha);
	t_vec3		n;

	n.y = p.y * cos_a - p.z * sin_a;
	n.z = p.y * sin_a + p.z * cos_a;
	n.x = p.x;
	return (n);
}

t_vec3	vec3_rotatey(t_vec3 p, float beta)
{
	const float	sin_b = sin(beta);
	const float	cos_b = cos(beta);
	t_vec3		n;

	n.x = p.x * cos_b + p.z * sin_b;
	n.z = -p.x * sin_b + p.z * cos_b;
	n.y = p.y;
	return (n);
}

t_vec3	vec3_rotatez(t_vec3 p, float gamma)
{
	const float	sin_g = sin(gamma);
	const float	cos_g = cos(gamma);
	t_vec3		n;

	n.x = p.x * cos_g - p.y * sin_g;
	n.y = p.x * sin_g + p.y * cos_g;
	n.z = p.z;
	return (n);
}
