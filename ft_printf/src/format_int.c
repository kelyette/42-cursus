/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:46:48 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/21 14:54:34 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

t_num	init_num(t_fspec *spec, long n)
{
	t_num	num;

	ft_bzero(&num, sizeof(num));
	num.n = n;
	num.base = 10;
	num.neg = (n < 0);
	if (spec->spec == 'x' || spec->spec == 'X')
		num.base = 16;
	num.len = ltoa_raw(num.str, n, num.base, spec->spec == 'X');
	num.tlen = num.len;
	if (!spec->precision && !num.n)
		num.tlen = 0;
	else if (spec->precision != -1 && spec->precision > num.tlen)
		num.tlen = spec->precision;
	return (num);
}

t_num	fputint_pre(t_fspec *spec, t_num num)
{
	char	pre;
	char	fsign;

	pre = 0;
	fsign = 0;
	if (num.base == 10 && spec->psign && !num.neg)
		fsign = '+';
	else if (num.base == 10 && spec->fillsign && !num.neg)
		fsign = ' ';
	else if (num.base == 10 && num.neg)
		pre = '-';
	if (num.base == 16 && spec->hexprefix && num.n)
		pre = '#';
	num.tlen += (fsign != 0) + (pre != 0) + (pre == '#');
	if (!spec->ljust && spec->width != -1 && !spec->zpad)
		fpad(spec->width, num.tlen, 0);
	if (fsign)
		fputchar(fsign);
	if (!(spec->precision || num.n))
		return (num);
	if (pre == '-')
		fputchar('-');
	else if (pre == '#')
		fputstr("0x");
	return (num);
}

void	fputint_base(t_fspec *spec, t_num num)
{
	if (spec->precision != -1)
		fpad(spec->precision, num.len, 1);
	else if (spec->width != -1 && spec->zpad)
		fpad(spec->width, num.tlen, 1);
	if (spec->precision || num.n)
		fputstr(num.str);
	if (spec->ljust && spec->width != -1 && !spec->zpad)
		fpad(spec->width, num.tlen, 0);
}

void	fmt_int(va_list *arg, t_fspec *spec)
{
	long	n;
	t_num	num;

	if (spec->spec == 'd' || spec->spec == 'i')
		n = va_arg(*arg, int);
	else
		n = (long)va_arg(*arg, unsigned int);
	num = init_num(spec, n);
	num = fputint_pre(spec, num);
	fputint_base(spec, num);
}
