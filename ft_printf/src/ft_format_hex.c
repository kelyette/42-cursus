/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:26:45 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 18:40:24 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_utils.h"
#include "ft_formats.h"

void	puthex_case_helper(long n, int ucase)
{
	if (n < 16)
	{
		ft_putchar_fd(hex_val(n, ucase), 1);
		return ;
	}
	puthex_case_helper(n / 16, ucase);
	ft_putchar_fd(hex_val(n % 16, ucase), 1);
}

static size_t
	fputhex_case(long n, int ucase, const t_format_spec *spec)
{
	const size_t	len = get_length_base(n, 16);

	justify(spec, len);
	pad_zero(spec, len);
	if (spec->precision || n)
	{
		if (spec->hexprefix)
			ft_putstr_fd("0x", 1);
		puthex_case_helper(n, ucase);
	}
	justify(spec, len);
	return (max(max(spec->width, spec->precision), len));
}

size_t	ft_fputhexlow(va_list *arg, const t_format_spec *spec)
{
	const unsigned int	v = va_arg(*arg, unsigned int);

	return (fputhex_case(v, 0, spec));
}

size_t	ft_fputhexup(va_list *arg, const t_format_spec *spec)
{
	const unsigned int	v = va_arg(*arg, unsigned int);

	return (fputhex_case(v, 1, spec));
}

size_t	ft_fputpointer(va_list *arg, const t_format_spec *spec)
{
	const long		v = va_arg(*arg, long);
	t_format_spec	cspec;

	ft_memcpy(&cspec, spec, sizeof(*spec));
	cspec.width -= 2;
	cspec.precision = sizeof(void *);
	cspec.hexprefix = 1;
	return (fputhex_case(v, 0, &cspec));
}
