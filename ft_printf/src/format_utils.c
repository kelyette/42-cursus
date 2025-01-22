/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:49:50 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/22 13:27:36 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include <unistd.h>
#define UCASEOFFSET -32
#define ZEROOFFSET   16

int	fputchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (1);
	g_char_count++;
	return (0);
}

int	fputstr(const char *str)
{
	while (*str)
		if (fputchar(*str++))
			return (1);
	return (0);
}

int	fpad(int width, int len, int zpad)
{
	const char	ch = ' ' + (ZEROOFFSET * zpad);

	while (len++ < width)
		if (fputchar(ch))
			return (1);
	return (0);
}

char	digitc(long n, int ucase)
{
	if (n < 0)
		n = -n;
	if (n < 10)
		return (n + '0');
	return (n - 10 + 'a' + (UCASEOFFSET * !!ucase));
}

int	ltoa_raw(char *dest, long n, int base, int ucase)
{
	int		len;
	int		i;
	long	tn;

	if (n == 0)
	{
		ft_memcpy(dest, "0", 2);
		return (1);
	}
	tn = n;
	len = 0;
	while (tn && ++len)
		tn /= base;
	i = len;
	dest[i] = 0;
	while (n)
	{
		dest[--i] = digitc(n % base, ucase);
		n /= base;
	}
	return (len);
}
