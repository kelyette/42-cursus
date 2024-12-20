/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:07:03 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/17 03:30:53 by kcsajka          ###   ########.fr       */
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

t_vec3	vec3_rotate(t_vec3 p, t_vec3 rot);
t_vec3	vec3_rotatex(t_vec3 p, float alpha);
t_vec3	vec3_rotatey(t_vec3 p, float beta);
t_vec3	vec3_rotatez(t_vec3 p, float gamma);

#endif
