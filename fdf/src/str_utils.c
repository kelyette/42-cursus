/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:04:13 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/12 18:38:55 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

char	*ftoa(float f, int precision)
{
	char	*res;
	char	*intpart;
	char	*fracpart;
	int		intlen;
	int		fraclen;

	if (!precision)
		return (ft_itoa((int)f));
	if (precision > 8)
		precision = 8;
	intpart = ft_itoa(abs((int)f));
	fracpart = ft_itoa((fabsf(f) - abs((int)f) + 1) * pow(10, precision));
	intlen = ft_strlen(intpart);
	fraclen = ft_strlen(fracpart) - 1;
	res = malloc(intlen + (f < 0) + fraclen + 2);
	if (f < 0)
		res[0] = '-';
	ft_memcpy(res + (f < 0), intpart, intlen);
	intlen += (f < 0);
	res[intlen] = '.';
	ft_memcpy(res + intlen + 1, fracpart + 1, fraclen);
	res[intlen + fraclen + 1] = 0;
	free(intpart);
	free(fracpart);
	return (res);
}

char	*v2toa(t_vec2 v, int precision)
{
	char	*res;
	char	*xstr;
	char	*ystr;
	int		xlen;
	int		ylen;

	xstr = ftoa(v.x, precision);
	ystr = ftoa(v.y, precision);
	xlen = ft_strlen(xstr);
	ylen = ft_strlen(ystr);
	res = malloc(xlen + ylen + 5);
	res[0] = '(';
	ft_memcpy(res + 1, xstr, xlen);
	res[xlen + 1] = ',';
	res[xlen + 2] = ' ';
	ft_memcpy(res + xlen + 3, ystr, ylen);
	res[xlen + ylen + 3] = ')';
	res[xlen + ylen + 4] = 0;
	free(xstr);
	free(ystr);
	return (res);
}

char	*v3toa(t_vec3 v, int precision)
{
	char	*res;
	char	*tmp;
	char	*zstr;
	int		tmplen;
	int		zlen;

	tmp = v2toa((t_vec2){v.x, v.y}, precision);
	zstr = ftoa(v.z, precision);
	tmplen = ft_strlen(tmp);
	zlen = ft_strlen(zstr);
	res = malloc(tmplen + zlen + 3);
	ft_memcpy(res, tmp, tmplen);
	res[tmplen - 1] = ',';
	res[tmplen] = ' ';
	ft_memcpy(res + tmplen + 1, zstr, zlen);
	res[tmplen + zlen + 1] = ')';
	res[tmplen + zlen + 2] = 0;
	free(tmp);
	free(zstr);
	return (res);
}
