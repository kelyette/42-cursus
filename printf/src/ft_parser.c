/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:12:25 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 17:59:52 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_formats.h"

static const char	g_spec_str_table[] = {
	'c',
	's',
	'd',
	'i',
	'u',
	'x',
	'X',
	'p',
	'%'
};

static t_ffptr		g_spec_func_table[] = {
	&ft_fputchar,
	&ft_fputstr,
	&ft_fputint,
	&ft_fputint,
	&ft_fputuint,
	&ft_fputhexlow,
	&ft_fputhexup,
	&ft_fputpointer,
	&ft_fputliteral,
};

static const int	g_spec_max = sizeof(g_spec_str_table) / sizeof(char);

static int	expect_flags(const char **fmtstr, t_format_spec *spec)
{
	char		*ftable;
	int			flagbit;
	int			flags;

	ftable = ft_strdup("\\-0");
	flags = 0;
	while (ft_strchr(ftable, **fmtstr))
	{
		flagbit = 1 << (ft_strchr(ftable, **fmtstr) - 1 - ftable);
		if (flagbit < 1)
		{
			printf("error: unknown flag '%c'\n", **fmtstr);
			return (0);
		}
		flags |= flagbit;
		++*fmtstr;
	}
	if (flags & (1 << 1))
		spec->zpad = 1;
	if (flags & (1 << 0))
	{
		spec->zpad = 0;
		spec->ljust = 1;
	}
	return (1);
}

static int	expect_width(va_list *arg, const char **fmtstr, t_format_spec *spec)
{
	const char	*str = *fmtstr;
	int			width;

	str = *fmtstr;
	width = 0;
	if (*str == '*')
		width = va_arg(*arg, int);
	while (ft_isdigit(*str))
		width = width * 10 + (*str++ - '0');
	spec->width = width;
	*fmtstr = str;
	return (1);
}

static int
	expect_precision(va_list *arg, const char **fmtstr, t_format_spec *spec)
{
	const char	*str;
	int			precision;

	str = *fmtstr;
	precision = 0;
	if (*str++ != '.')
		return (1);
	if (*str == '*')
		precision = va_arg(*arg, int);
	while (ft_isdigit(*str))
		precision = precision * 10 + (*str++ - '0');
	spec->precision = precision;
	*fmtstr = str;
	return (1);
}

static int	expect_specifier(const char **fmtstr, t_format_spec *spec)
{
	int	i;

	i = -1;
	while (++i < g_spec_max)
	{
		if (**fmtstr == g_spec_str_table[i])
		{
			(*fmtstr)++;
			spec->func = g_spec_func_table[i];
			return (1);
		}
	}
	return (0);
}

int	spec_expect_all(va_list *arg, const char **fmtstr, t_format_spec *spec)
{
	if (!expect_flags(fmtstr, spec))
		return (0);
	if (!expect_width(arg, fmtstr, spec))
		return (0);
	if (!expect_precision(arg, fmtstr, spec))
		return (0);
	if (!expect_specifier(fmtstr, spec))
		return (0);
	return (1);
}
