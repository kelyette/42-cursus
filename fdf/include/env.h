/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:03:03 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/18 02:01:02 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_loopstate	t_ls;
typedef struct s_heightmap	t_hmap;
typedef struct s_drawbuffer	t_dbuf;

typedef struct s_prefs
{
	int	clr_bg;
	int	clr_fg;
	int	clr_hi;
}	t_prefs;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_prefs	prefs;
	t_hmap	*hmap;
	t_ls	*ls;
	t_dbuf	*drawbuf;
}	t_env;

#endif
