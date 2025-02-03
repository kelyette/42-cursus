/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:05:24 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 17:38:33 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAP_H
# define HMAP_H
# include <errno.h>
# include "libft.h"

# include "env.h"
# include "geometry.h"

typedef struct s_heightmap_point
{
	t_vec3	pos;
	t_clr	color;
}	t_hpt;

typedef struct s_heightmap
{
	t_vec3	size;
	t_vec3	pos;
	t_vec3	origin_offset;
	t_vec3	rot;
	t_vec3	scale;
	t_vec2	offset;
	t_hpt	*map;
}	t_hmap;

int		init_hmap(t_env *env, const char *filename);

// utils
void	print_hmap(t_hpt *map, t_vec2 size);
int		free_split(char **split);

// parsing
int		safe_open(int *fd, const char *path, int oflag);
int		get_hmap_size(const char *path, int *xptr, int *yptr);
int		parse_hmap_line(t_hpt *map, const char *line, int xlen, int ypos);

t_hpt	hmap_getpt(t_hmap *hmap, t_vec2 pos);
t_vec2	point2screen_iso(t_hmap *hmap, t_vec3 p);

#endif
