/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:04:59 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/22 13:47:07 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#ifdef __linux__
# define NOFLAGPSIGN 1
# define NULLSTR "(null)"
# define NWIDTHREQ 1
#else
# define NOFLAGPSIGN 0
# define NULLSTR "(null)"
# define NWIDTHREQ 0
#endif

int	fmt_char(va_list *arg, t_fspec *spec)
{
	char	c;

	if (spec->spec == '%')
		c = '%';
	else
		c = va_arg(*arg, int);
	if (spec->spec == '%' && NOFLAGPSIGN)
	{
		if (fputchar('%'))
			return (1);
		return (0);
	}
	if (spec->width != -1 && spec->spec == '%' && spec->zpad
		&& fpad(spec->width, 1, 1))
		return (1);
	else if (!spec->ljust && spec->width != -1
		&& fpad(spec->width, 1, 0))
		return (1);
	if (fputchar(c))
		return (1);
	if (spec->ljust && spec->width != -1 && !spec->zpad
		&& fpad(spec->width, 1, 0))
		return (1);
	return (0);
}

static int	fputstrn(const char *str, int n)
{
	while (n-- > 0)
		if (fputchar(*str++))
			return (1);
	return (0);
}

int	fmt_str(va_list *arg, t_fspec *spec)
{
	const char	nullstr[] = NULLSTR;
	char		*str;
	int			len;
	int			isnull;

	str = va_arg(*arg, char *);
	isnull = !str;
	if (!str)
		str = (char *)nullstr;
	len = ft_strlen(str);
	if (isnull && NWIDTHREQ && spec->precision != -1 && len > spec->precision)
	{
		str = "";
		len = 0;
	}
	if (spec->precision != -1 && len > spec->precision)
		len = spec->precision;
	if (!spec->ljust && spec->width != -1 && fpad(spec->width, len, 0))
		return (1);
	if (fputstrn(str, len))
		return (1);
	if (spec->ljust && spec->width != -1 && fpad(spec->width, len, 0))
		return (1);
	return (0);
}
