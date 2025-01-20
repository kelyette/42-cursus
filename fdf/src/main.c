/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:47:24 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/06 15:32:16 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	error(t_env *env, int fatal, const char *msg)
{
	ft_printf("fdf: error: %s\n", msg);
	if (fatal)
		fdfclose(env);
	return (1);
}

static void	init_prefs(t_env *env)
{
	mlx_do_key_autorepeatoff(env->mlx);
	env->prefs.clr_bg = 0xcdcdcd;
	env->prefs.clr_fg = 0xaaaaaa;
	env->prefs.clr_hi = 0x8000ff;
}

static void	init_mlx(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1270, 720, "FDF v0.0 - kcsajka");
}

int	main(int argc, char **argv)
{
	static t_env	env;
	//int		map[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,10,10,0,0,0,10,10,10,10,10,0,0,0,0,0,10,10,0,0,10,10,0,0,0,0,0,0,0,10,10,0,0,0,0,10,10,0,0,10,10,0,0,0,0,0,0,0,10,10,0,0,0,0,10,10,10,10,10,10,0,0,0,0,10,10,10,10,0,0,0,0,0,0,10,10,10,10,10,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//int	map[] = {0,2,4,4,4,5,4,4,4,2,0,2,4,5,4,4,4,4,4,5,4,2,4,5,4,3,3,2,3,3,4,5,4,4,4,3,2,1,1,1,2,3,4,4,4,4,3,1,0,0,0,1,3,4,4,5,4,2,1,0,0,0,1,2,4,5,4,4,3,1,0,0,0,1,3,4,4,4,4,3,2,1,1,1,2,3,4,4,4,5,4,3,3,2,3,3,4,5,4,2,4,5,4,4,4,4,4,5,4,2,0,2,4,4,4,5,4,4,4,2,0};

	ft_bzero(&env, sizeof(env));
	if (argc < 2 || init_hmap(&env, argv[1]))
		return (1);
	//env.hmap->map = map;
	//env.hmap->size = (t_vec3){11, 11, 5};
	init_mlx(&env);
	init_prefs(&env);
	init_drawers(&env);
	init_hooks(&env);
	init_loop(&env);
	mlx_loop(env.mlx);
}
