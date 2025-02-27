/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:47:24 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/27 14:47:53 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	fdfclose(t_env *env, int code)
{
	if (env && env->mlx && env->win)
	{
		mlx_destroy_image(env->mlx, env->drawbuf->mlximg);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_display(env->mlx);
		free(env->mlx);
	}
	if (env && env->hmap->map)
		free(env->hmap->map);
	if (env && env->ls->info)
		free_info(env->ls->info, env->ls->info_count);
	exit(code);
	return (0);
}

static void	init_prefs(t_env *env)
{
	env->colors.bg = int2clr(0xcdcdcd);
	env->colors.fg = int2clr(0xaaaaaa);
	env->colors.hi = int2clr(0x8000ff);
}

static void	init_mlx(t_env *env)
{
	env->wsize_x = 2560;
	env->wsize_y = 1440;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->wsize_x, env->wsize_y, "FDF");
}

int	main(int argc, char **argv)
{
	static t_env	env = {0};

	if (argc != 2
		&& ft_printf("usage: %s <map.fdf>\n", argv[0]))
		return (1);
	init_mlx(&env);
	if (init_hmap(&env, argv[1]))
		return (1);
	init_prefs(&env);
	init_drawers(&env);
	init_hooks(&env);
	init_loop(&env);
	mlx_loop(env.mlx);
	fdfclose(&env, 0);
}
