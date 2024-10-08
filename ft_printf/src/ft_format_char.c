/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:57 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/05 13:16:34 by kcsajka          ###   ########.fr       */
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

size_t	ft_fputstr(va_list *arg, const t_format_spec *spec)
{
	char	*v;
	size_t	len;
	size_t	plen;
	char	*rstr;
	char	*strnull;

	strnull = NULL;
	v = va_arg(*arg, char *);
	if (!v)
	{
		strnull = ft_strdup("(null)");
		v = strnull;
	}
	len = ft_strlen(v);
	plen = min(spec->precision, len);
	rstr = ft_substr(v, 0, plen);
	justify(spec, len);
	ft_putstr_fd(rstr, 1);
	justify(spec, len);
	if (strnull)
		free(strnull);
	free(rstr);
	return (1);
}
