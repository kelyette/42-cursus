/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:12:25 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/19 16:29:40 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_format.h"

int	expect_flags(const char **format, t_fspec *spec)
{
	const char	ftable[] = "\\-+ #0";
	int			flagbit;
	int			flags;

	flags = 0;
	while (ft_strchr(ftable, **format))
	{
		flagbit = 1 << (ft_strchr(ftable, **format) - 1 - ftable);
		if (flagbit < 1)
			break ;
		flags |= flagbit;
		++*format;
	}
	spec->ljust = flags & (1 << 0) && 1;
	spec->psign = flags & (1 << 1) && 1;
	spec->fillsign = flags & (1 << 2) && !spec->psign;
	spec->hexprefix = flags & (1 << 3) && 1;
	spec->zpad = flags & (1 << 4) && !spec->ljust;
	return (0);
}

int	expect_width(va_list *arg, const char **format, t_fspec *spec)
{
	const char	*str = *format;
	int			width;

	width = 0;
	if (*str == '*')
	{
		str++;
		width = va_arg(*arg, int);
		if (width < 0)
		{
			if (width == INT_MIN)
				width = INT_MAX;
			else
				width = -width;
			spec->ljust = 1;
		}
	}
	while (ft_isdigit(*str))
		width = width * 10 + (*str++ - '0');
	spec->width = width;
	*format = str;
	return (0);
}

int	expect_precision(va_list *arg, const char **format, t_fspec *spec)
{
	const char	*str = *format;
	int			precision;

	precision = 0;
	if (*str++ != '.')
		return (0);
	spec->precision = 0;
	if (*str == '*')
	{
		spec->precision = va_arg(*arg, int);
		*format = ++str;
		return (0);
	}
	while (ft_isdigit(*str))
		precision = precision * 10 + (*str++ - '0');
	spec->precision = precision;
	*format = str;
	return (0);
}

int	expect_specifier(const char **format, t_fspec *spec)
{
	static const char		*spec_char[] = {"di", "uxX", "feg", "c%", "s", "n"};
	static const t_ffptr	spec_func[] = {
		&ft_fint, &ft_fuint, &ft_ffloat, &ft_fchar, &ft_fstr, &ft_counter
	};
	int						i;

	i = sizeof(spec_func) / sizeof(spec_func[0]);
	while (i-- > 0)
	{
		if (ft_strchr(spec_char[i], **format))
		{
			spec->spec = **format;
			(*format)++;
			spec->func = spec_func[i];
			return (0);
		}
	}
	return (1);
}

/*int	expect_length(const char **format, t_fspec *spec)
{
	const char	*mods[] = {0, "l", "h", "ll", "hh"};
	const int	vals[] = {SIZE_NONE, SIZE_L, SIZE_H, SIZE_LL, SIZE_HH};
	int			i;

	i = sizeof(mods) / sizeof(mods[0]);
	while (--i > 0)
		if (!ft_strncmp(mods[i], *format, ft_strlen(mods[i])))
			break ;
	spec->size = vals[i];
	return (0);
}*/
