/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:57 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 16:58:42 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_utils.h"
#include "ft_formats.h"

size_t	ft_fputchar(va_list *arg, const t_format_spec *spec)
{
	const char	v = va_arg(*arg, int);

	justify(spec, 1);
	ft_putchar_fd(v, 1);
	justify(spec, 1);
	return (1);
}

size_t	ft_fputliteral(va_list *arg, const t_format_spec *spec)
{
	(void)arg;
	justify(spec, 1);
	ft_putchar_fd('%', 1);
	justify(spec, 1);
	return (1);
}

static const char	*strornull(va_list *arg)
{
	const char	*v = va_arg(*arg, char*);

	if (!v)
		return (ft_strdup("(null)"));
	return (v);
}

size_t	ft_fputstr(va_list *arg, const t_format_spec *spec)
{
	const char		*v = strornull(arg);
	const size_t	len = ft_strlen(v);
	const size_t	plen = min(spec->precision, len);

	justify(spec, len);
	ft_putstr_fd(ft_substr(v, 0, plen), 1);
	justify(spec, len);
	return (1);
}
