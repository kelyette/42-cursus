/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char.c                                            ) . . (      */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:57 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/08 19:01:32 by kcsajka                     /| | | |\    */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_utils.h"
#include "ft_formats.h"

size_t	ft_fputchar(va_list *arg, const t_format_spec *spec)
{
	const char	v = va_arg(*arg, int);

	justify(spec, 1);
	ft_putchar_fd(v, 1);
	justify(spec, 1);
	return (1);
}

size_t	ft_fputliteral(va_list *arg, const t_format_spec *spec)
{
	(void)arg;
	justify(spec, 1);
	ft_putchar_fd('%', 1);
	justify(spec, 1);
	return (1);
}

static const char	*strornull(va_list *arg, const char *nullstr)
{
	const char	*v = va_arg(*arg, char *);

	if (!v)
		return (nullstr);
	return (v);
}

size_t	ft_fputstr(va_list *arg, const t_format_spec *spec)
{
	const char	nullstr[] = "(null)";
	const char	*v = strornull(arg, nullstr);
	size_t		len;
	size_t		wlen;

	len = ft_strlen(v);
	if (spec->precision != -1)
		len = spec->precision;
	wlen = max(spec->width, len);
	justify(spec, wlen - len);
	ft_putstr_fd(ft_substr(v, 0, len), 1);
	justify(spec, wlen - len);
	return (1);
}
