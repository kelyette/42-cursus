/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:30:56 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/07 16:47:56 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "ft_format.h"

static void	zpad_c(int size)
{
	while (size-- > 0)
		fputchar('0');
}

void	ft_fchar(va_list *arg, t_fspec *spec)
{
	char	v;

	if (spec->spec == '%')
		v = '%';
	else if (spec->size == SIZE_L)
		v = va_arg(*arg, wint_t);
	else
		v = va_arg(*arg, int);
	fjustify(0, spec, 1);
	if (spec->spec == '%' && spec->width != -1 && spec->zpad)
		zpad_c(spec->width - 1);
	fputchar(v);
	fjustify(1, spec, 1);
}
