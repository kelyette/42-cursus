/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:18:19 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/15 14:39:12 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWERS_H
# define DRAWERS_H
# include "mlx.h"
# include "libft.h"

# include "env.h"
# include "log.h"
# include "hmap.h"
# include "geometry.h"

typedef struct s_encoding
{
	int		bitspp;
	int		endian;
	int		line_size;
}	t_encd;

typedef struct s_drawbuffer
{
	void	*mlximg;
	int		*data;
	int		updated;
	t_encd	encoding;
	t_rect	rect;
}	t_dbuf;

int	init_drawers(t_env *env);

int	draw_line(t_env *env, t_vec2 p1, t_vec2 p2, int color);
int	draw_axes(t_env *env);
int	draw_hmap(t_env *env);

#endif
