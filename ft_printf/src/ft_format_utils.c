/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:59:37 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 14:07:45 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_formats.h"
#include "ft_utils.h"

int	g_justified = 1;

void	justify_output(char c, size_t size)
{
	if (size < 1)
		return ;
	while (size-- > 0)
		ft_putchar_fd(c, 1);
}

void	justify(const t_format_spec *spec, int len)
{
	const size_t	width_diff = \
						max(0, spec->width - max(spec->precision, len));
	const char		pad_char = ' ' + (ZPADOFFSET * spec->zpad);

	if (g_justified ^ spec->ljust)
		justify_output(pad_char, width_diff);
	g_justified ^= 1;
	fflush(stdout);
}

void	pad_zero(const t_format_spec *spec, size_t len)
{
	size_t	precise_diff;

	precise_diff = max(0, spec->precision - len);
	justify_output('0', precise_diff);
}
