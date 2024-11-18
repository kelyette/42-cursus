/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:09:28 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/07 13:22:35 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_format.h"

static t_llong	abs_llong(t_llong n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	len_llong(t_llong n, int precision, int base)
{
	const int	signd = n < 0;
	int			len;

	if (!precision && !n)
		return (0);
	len = !n + signd;
	while (n && ++len)
		n /= base;
	if (len < precision + signd)
		len = precision + signd;
	return (len);
}

static void	fput_llong(t_llong n, int pad, int absolute)
{
	static int	depth = -1;

	depth++;
	if (-10 < n && n < 10)
	{
		if (n < 0 && (!absolute || ++depth))
			fputchar('-');
		while (++depth < pad)
			fputchar('0');
		fputchar(abs_llong(n) + '0');
		depth = -1;
		return ;
	}
	fput_llong(n / 10, pad, absolute);
	fputchar(abs_llong(n) % 10 + '0');
}

void	ft_fint(va_list *arg, t_fspec *spec)
{
	t_llong	v;
	int		len;
	int		zpad;
	int		absolute;

	if (spec->size == SIZE_HH)
		v = (signed char)va_arg(*arg, int);
	else if (spec->size == SIZE_H)
		v = (short)va_arg(*arg, int);
	else if (spec->size == SIZE_L)
		v = va_arg(*arg, long int);
	else if (spec->size == SIZE_LL)
		v = va_arg(*arg, long long int);
	else
		v = va_arg(*arg, int);
	len = len_llong(v, spec->precision, 10);
	get_zpad_int(spec, &zpad, &absolute);
	fjustify(0, spec, len);
	if (v || spec->precision)
		fput_llong(v, zpad, absolute);
	fjustify(1, spec, len);
}
