/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:07:03 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/15 23:57:06 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H
# include <math.h>

typedef struct t_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_rect
{
	t_vec2	pos;
	t_vec2	size;
	t_vec2	origin;
}	t_rect;

// operations
t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subs(t_vec3 a, t_vec3 b);
t_vec3	vec3_mag(t_vec3 v, int f);

// rotation
t_vec3	vec3_rotate(t_vec3 p, t_vec3 rot);
t_vec3	vec3_rotatex(t_vec3 p, float alpha);
t_vec3	vec3_rotatey(t_vec3 p, float beta);
t_vec3	vec3_rotatez(t_vec3 p, float gamma);

// projection
t_vec2	project_iso(t_vec3 v3, t_vec3 rot, t_vec2 offset);

#endif
