/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:28:18 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/10 18:24:25 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "ft_format.h"

static const char
	*get_vaarg(va_list *arg, enum e_size size, const char *nullstr)
{
	const char	*v;

	if (size == SIZE_L)
		v = (const char *)va_arg(*arg, wchar_t *);
	else
		v = va_arg(*arg, char *);
	if (!v)
		return (nullstr);
	return (v);
}

void	ft_fstr(va_list *arg, t_fspec *spec)
{
	const char	nullstr[] = "(null)";
	const char	*v = get_vaarg(arg, spec->size, nullstr);

	(void)v;
}
