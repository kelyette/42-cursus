/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:05:24 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/18 02:00:46 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAP_H
# define HMAP_H
# include "env.h"
# include "geometry.h"

typedef struct s_heightmap
{
	t_vec3	size;
	t_vec3	pos;
	t_vec3	origin;
	t_vec3	rot;
	t_vec3	scale;
	t_vec2	offset;
	int		*map;
}	t_hmap;

int		init_hmap(t_env *env, const char *filename);

// utils
t_vec3	hmap_getpt(t_hmap *hmap, t_vec2 pos);
t_vec2	vec3to2_iso(t_hmap *hmap, t_vec3 v3);
t_vec2	map2screen_iso(t_hmap *hmap, t_vec2 pos);

#endif
