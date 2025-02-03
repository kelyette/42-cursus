/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:47:24 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/03 19:41:03 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	error(t_env *env, int fatal, const char *msg)
{
	ft_printf("fdf: error: %s\n", msg);
	if (fatal)
		fdfclose(env, 1);
	return (1);
}

static void	init_prefs(t_env *env)
{
	mlx_do_key_autorepeatoff(env->mlx);
	env->colors.bg = int2clr(0xcdcdcd);
	env->colors.fg = int2clr(0xaaaaaa);
	env->colors.hi = int2clr(0x8000ff);
}

static void	init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1270, 720, "FDF v0.0 - kcsajka");
	env->wsize_x = 1270;
	env->wsize_y = 720;
}

int	main(int argc, char **argv)
{
	static t_env	env = {0};

	if (argc < 2 || argc == 3)
	{
		ft_printf("usage: %s <map.fdf> [<X size> <Y size>]\n", argv[0]);
		return (1);
	}
	if (init_hmap(&env, argv[1]))
		return (1);
	init_mlx(&env);
	init_prefs(&env);
	init_drawers(&env);
	init_hooks(&env);
	init_loop(&env);
	mlx_loop(env.mlx);
}
