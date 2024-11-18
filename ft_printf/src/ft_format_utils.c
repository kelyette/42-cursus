/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:48:26 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/07 13:26:41 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_format.h"
#include <unistd.h>

void	fputchar(char c)
{
	g_char_count++;
	write(1, &c, 1);
}

void	fjustify(int after, const t_fspec *spec, int len)
{
	if (spec->width == -1 || spec->zpad || (spec->ljust != after))
		return ;
	while (len++ < spec->width)
		fputchar(' ');
}

void	get_zpad_int(const t_fspec *spec, int *zpad, int *absolute)
{
	if (absolute)
		*absolute = 0;
	*zpad = 0;
	if (spec->width != -1 && spec->zpad)
	{
		if (absolute)
			*absolute = 1;
		*zpad = spec->width;
	}
	if (spec->precision != -1)
		*zpad = spec->precision;
}
