/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:09:28 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 13:56:43 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_formats.h"
#include "ft_utils.h"

static void	fputlong(long n)
{
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', 1);
		return ;
	}
	fputlong(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
}

static size_t	fputint_generic(long n, const t_format_spec *spec)
{
	const size_t	len = get_length_base(n, 10);

	justify(spec, len);
	pad_zero(spec, len);
	if (spec->precision || n)
		fputlong(n);
	justify(spec, len);
	return (1);
}

size_t	ft_fputint(va_list *arg, const t_format_spec *spec)
{
	const int	v = va_arg(*arg, int);

	return (fputint_generic(v, spec));
}

size_t	ft_fputuint(va_list *arg, const t_format_spec *spec)
{
	const unsigned int	v = va_arg(*arg, unsigned int);

	return (fputint_generic(v, spec));
}
