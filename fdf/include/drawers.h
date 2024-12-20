/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:18:19 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/19 15:57:29 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWERS_H
# define DRAWERS_H
# include "mlx.h"
# include "libft.h"

# include "env.h"
# include "hmap.h"
# include "geometry.h"

typedef struct s_drawbuffer
{
	void	*img;
	int		*rawdata;
	int		updated;
	int		pos;
}	t_dbuf;

int	init_drawers(t_env *env);

int	draw_line(t_env *env, t_vec2 p1, t_vec2 p2);
int	draw_hmap(t_env *env);
int	draw_axes(t_env *env);

#endif
