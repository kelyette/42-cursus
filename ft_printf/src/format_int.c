/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:46:48 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/17 19:27:25 by kcsajka          ###   ########.fr       */
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
	else if (spec->spec == 'b')
		num.base = 2;
	num.len = ltoa_raw(num.str, n, num.base, spec->spec == 'X');
	num.tlen = num.len;
	if (!spec->precision && !num.n)
		num.tlen = 0;
	else if (spec->precision != -1 && spec->precision > num.tlen)
		num.tlen = spec->precision;
	return (num);
}

int	fputint_pre(t_fspec *spec, t_num *num)
{
	if (num->base == 10 && spec->psign && !num->neg)
		num->fsign = '+';
	else if (num->base == 10 && spec->fillsign && !num->neg)
		num->fsign = ' ';
	else if (num->base == 10 && num->neg)
		num->pre[0] = '-';
	if (num->base == 16 && spec->hexprefix && num->n)
	{
		num->pre[0] = '0';
		num->pre[1] = 'x' - (spec->spec == 'X') * 32;
	}
	num->tlen += (num->fsign != 0) + (num->pre[0] != 0) + (num->pre[0] == '0');
	if (!spec->ljust && spec->width != -1 && !spec->zpad
		&& fpad(spec->width, num->tlen, 0))
		return (1);
	if ((spec->precision || num->n) && num->fsign && fputchar(num->fsign))
		return (1);
	if (num->pre[0] != 0 && fputstr(num->pre))
		return (1);
	return (0);
}

int	fputint_base(t_fspec *spec, t_num num)
{
	if (spec->precision != -1 && fpad(spec->precision, num.len, 1))
		return (1);
	else if (spec->width != -1 && spec->zpad && fpad(spec->width, num.tlen, 1))
		return (1);
	if (spec->precision || num.n)
		if (fputstr(num.str))
			return (1);
	if (spec->ljust && spec->width != -1 && !spec->zpad
		&& fpad(spec->width, num.tlen, 0))
		return (1);
	return (0);
}

int	fmt_int(va_list *arg, t_fspec *spec)
{
	long	n;
	t_num	num;

	if (spec->spec == 'd' || spec->spec == 'i')
		n = va_arg(*arg, int);
	else
		n = (long)va_arg(*arg, unsigned int);
	num = init_num(spec, n);
	if (fputint_pre(spec, &num) || fputint_base(spec, num))
		return (1);
	return (0);
}
