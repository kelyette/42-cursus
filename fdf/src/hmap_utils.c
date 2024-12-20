/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:22:07 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/18 22:56:06 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmap.h"

t_vec3	hmap_getpt(t_hmap *hmap, t_vec2 pos)
{
	t_vec3	r;

	r.x = pos.x;
	r.y = pos.y;
	r.z = hmap->map[(int)(pos.y * hmap->size.x + pos.x)];
	return (r);
}
// MOVE ORIGIN AND OFFSET CALCULATION FROM FUNCTION UNDER TO ABOVE
t_vec2	vec3to2_iso(t_hmap *hmap, t_vec3 v3)
{
	t_vec2			v2;
	const t_vec3	pos = hmap->pos;
	const t_vec3	scale = hmap->scale;
	const t_vec3	rot = hmap->rot;

	v3.x = (pos.x + v3.x - hmap->size.x * hmap->origin.x) * scale.x;
	v3.y = (pos.y + v3.y - hmap->size.y * hmap->origin.y) * scale.y;
	v3.z = (pos.z + v3.z - hmap->size.z * hmap->origin.z) * scale.z;
	v3 = vec3_rotate(v3, rot);
	v2.x = (-cos(0.5) * v3.x + cos(0.5) * v3.y) + pos.x + hmap->offset.x;
	v2.y = (-cos(1) * v3.x + -cos(1) * v3.y + v3.z) + pos.y + hmap->offset.y;
	return (v2);
}

t_vec2	map2screen_iso(t_hmap *hmap, t_vec2 pos)
{
	t_vec3	world_pt;
	t_vec2	screen_pt;

	world_pt = hmap_getpt(hmap, pos);
	screen_pt = vec3to2_iso(hmap, world_pt);
	screen_pt.x += hmap->pos.x;
	screen_pt.y += hmap->pos.y;
	return (screen_pt);
}
