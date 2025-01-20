/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:05:24 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/16 16:35:40 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAP_H
# define HMAP_H
# include <errno.h>
# include "libft.h"

# include "env.h"
# include "geometry.h"

typedef struct s_point
{
	t_vec3	pos;
	int		color;
}	t_pt;

typedef struct s_heightmap
{
	t_vec3	size;
	t_vec3	pos;
	t_vec3	origin;
	t_vec3	rot;
	t_vec3	scale;
	t_vec2	offset;
	t_pt	*map;
}	t_hmap;

int		init_hmap(t_env *env, const char *filename);

// utils
void	print_hmap(t_pt *map, t_vec2 size);

// parsing
int		safe_open(int *fd, const char *path, int oflag);
int		parse_xlength(const char *path, int *xptr, int *yptr);
int		parse_hmap_line(t_pt **mapptr, const char *line, int xlen);

t_vec3	hmap_getpt(t_hmap *hmap, t_vec2 pos);
t_vec2	map2screen_iso(t_hmap *hmap, t_vec2 pos);

#endif
