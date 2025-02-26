/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:03:03 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/26 17:34:32 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "geometry.h"

typedef struct s_loopstate	t_ls;
typedef struct s_heightmap	t_hmap;
typedef struct s_drawbuffer	t_dbuf;

typedef struct s_colorscheme
{
	t_clr	bg;
	t_clr	fg;
	t_clr	hi;
}	t_csch;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	int		wsize_x;
	int		wsize_y;
	t_csch	colors;
	t_hmap	*hmap;
	t_ls	*ls;
	t_dbuf	*drawbuf;
}	t_env;

int	fdfclose(t_env *env, int code);

#endif
