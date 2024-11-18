/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:31:30 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/06 17:28:42 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_format.h"

static void	apply_limit(t_fspec *spec)
{
	if (ULIMIT < 1)
		return ;
	if (spec->width > ULIMIT)
		spec->width = ULIMIT;
	if (spec->precision > ULIMIT)
		spec->precision = ULIMIT;
	if (spec->ljust && spec->zpad)
		spec->zpad = 0;
}

int	spec_parse(va_list *arg, const char **format, t_fspec *spec)
{
	if (expect_flags(format, spec))
		return (1);
	if (expect_width(arg, format, spec))
		return (2);
	if (expect_precision(arg, format, spec))
		return (3);
	if (expect_length(format, spec))
		return (4);
	if (expect_specifier(format, spec))
		return (5);
	spec_parse_post(spec);
	return (0);
}

void	spec_parse_post(t_fspec *spec)
{
	apply_limit(spec);
	if (spec->spec != '%' && spec->precision != -1)
		spec->zpad = 0;
	if (spec->ljust)
		spec->zpad = 0;
}

static int	handle_specifier(va_list *value, const char **format)
{
	t_fspec	spec;
	int		parse_rval;

	ft_bzero(&spec, sizeof(spec));
	spec.width = -1;
	spec.precision = -1;
	parse_rval = spec_parse(value, format, &spec);
	if (parse_rval)
		return (parse_rval);
	(*spec.func)(value, &spec);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	//int		put_rvalue;
	int		tmp_length;

	g_char_count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			/*put_rvalue = */handle_specifier(&args, &format);
			/*if (put_rvalue && BTHROWERR)
				return (fmterr(put_rvalue));*/
			continue ;
		}
		fputchar(*format++);
	}
	va_end(args);
	tmp_length = g_char_count;
	g_char_count = 0;
	return (tmp_length);
}
