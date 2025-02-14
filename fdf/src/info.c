/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:55:55 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/12 18:46:45 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#define IN_XOFFSET 30
#define IN_XVALOFFSET 100
#define IN_YINCREMENT 30
#define IN_YINITIAL 30

int	init_info(t_env *env)
{
	static t_info	infonodes[] = {
	{"delta:", NULL, 1, 1, NULL},
	{"position:", NULL, 2, 0, NULL},
	{"rotation:", NULL, 3, 2, NULL},
	{"scale:", NULL, 3, 2, NULL},
	{"size:", NULL, 3, 0, NULL}};
	int				i;

	i = 0;
	infonodes[i++].valptr = &env->ls->delta;
	infonodes[i++].valptr = &env->hmap->offset;
	infonodes[i++].valptr = &env->hmap->rot;
	infonodes[i++].valptr = &env->hmap->scale;
	infonodes[i++].valptr = &env->hmap->size;
	env->ls->info = infonodes;
	env->ls->info_count = i;
	return (0);
}

void	update_inode(t_info *node)
{
	if (node->valstr)
		free(node->valstr);
	node->valstr = NULL;
	if (node->type == 0)
		node->valstr = ft_itoa(*(int *)node->valptr);
	else if (node->type == 1)
		node->valstr = ftoa(*(float *)node->valptr, node->precision);
	else if (node->type == 2)
		node->valstr = v2toa(*(t_vec2 *)node->valptr, node->precision);
	else if (node->type == 3)
		node->valstr = v3toa(*(t_vec3 *)node->valptr, node->precision);
}

void	update_info(t_env *env)
{
	int	count;

	count = env->ls->info_count;
	while (count--)
		update_inode(&env->ls->info[count]);
}

void	draw_info(t_env *env)
{
	int		i;
	int		yoff;
	t_info	*info;

	i = -1;
	yoff = IN_YINITIAL;
	info = env->ls->info;
	while (++i < env->ls->info_count)
	{
		update_inode(&info[i]);
		mlx_string_put(env->mlx, env->win,
			IN_XOFFSET, yoff, 0xffffff, info[i].title);
		mlx_string_put(env->mlx, env->win,
			IN_XOFFSET + IN_XVALOFFSET, yoff, 0xffffff, info[i].valstr);
		yoff += IN_YINCREMENT;
	}
}

void	free_info(t_info *info, int count)
{
	if (!info)
		return ;
	while (count--)
	{
		if (info[count].valstr)
		{
			free(info[count].valstr);
			info[count].valstr = NULL;
		}
	}
}
