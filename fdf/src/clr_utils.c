/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:40:39 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/04 15:47:26 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

inline int	clr2int(t_clr clr)
{
	return (clr.r << 16 | clr.g << 8 | clr.b);
}

t_clr	int2clr(int clr)
{
	t_clr	res;

	res.r = (clr & 0xff0000) >> 16;
	res.g = (clr & 0x00ff00) >> 8;
	res.b = (clr & 0x0000ff);
	res.val = clr;
	return (res);
}

t_clr	grad_lerp(t_grad grad, float t)
{
	if (t < 0 || grad.b.val == -1)
		return (grad.a);
	if (t > 1)
		return (grad.b);
	grad.a.r += (grad.b.r - grad.a.r) * t;
	grad.a.g += (grad.b.g - grad.a.g) * t;
	grad.a.b += (grad.b.b - grad.a.b) * t;
	grad.a.val = clr2int(grad.a);
	return (grad.a);
}
