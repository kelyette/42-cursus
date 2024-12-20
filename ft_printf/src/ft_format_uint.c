/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:34:25 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/26 17:28:30 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_format.h"

static int	len_ullong(t_fspec *spec, t_ullong n, int base)
{
	int	len;

	if (!spec->precision && !n)
		return (0);
	len = !n + (spec->hexprefix && base == 16) * 2;
	while (n && ++len)
		n /= base;
	if (len < spec->precision)
		return (spec->precision);
	return (len);
}

static char	digit_char(t_ullong n, int ucase)
{
	char		offset;

	if (n > 35)
		return ('?');
	offset = '0';
	if (n > 9)
		offset = 'a' + (!!ucase * CASEOFFSET) - 10;
	return (n + offset);
}

static void	fput_ullong(t_ullong n, int pad, int base, int ucase)
{
	static int	depth = -1;

	depth++;
	if (n < (t_ullong)base)
	{
		while (++depth < pad)
			fputchar('0');
		fputchar(digit_char(n, ucase));
		depth = -1;
		return ;
	}
	fput_ullong(n / base, pad, base, ucase);
	fputchar(digit_char(n % base, ucase));
}

static void	spec_parse_u(t_fspec *spec, int *zpad, int *base, int *ucase)
{
	get_zpad_int(spec, zpad, NULL);
	*base = 10;
	*ucase = 1;
	if (spec->spec == 'x' || spec->spec == 'X')
		*base = 16;
	if (spec->spec == 'x')
		*ucase = 0;
}

void	ft_fuint(va_list *arg, t_fspec *spec)
{
	t_ullong	v;
	int			len;
	int			zpad;
	int			base;
	int			ucase;

	if (spec->size == SIZE_HH)
		v = (unsigned char)va_arg(*arg, unsigned int);
	if (spec->size == SIZE_H)
		v = (unsigned short)va_arg(*arg, unsigned int);
	if (spec->size == SIZE_L)
		v = va_arg(*arg, unsigned long int);
	if (spec->size == SIZE_LL)
		v = va_arg(*arg, unsigned long long int);
	else
		v = va_arg(*arg, unsigned int);
	spec_parse_u(spec, &zpad, &base, &ucase);
	len = len_ullong(spec, v, base);
	fjustify(0, spec, len);
	if (v && base == 16 && spec->hexprefix)
		fputstr("0x");
	if (v || spec->precision)
		fput_ullong(v, zpad, base, ucase);
	fjustify(1, spec, len);
}
