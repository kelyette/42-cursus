/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:28:18 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/21 18:14:31 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "libft.h"
#include "ft_format.h"

static void	putstrn_char(const void *str, int len)
{
	int				i;

	i = -1;
	while (++i < len)
		fputchar(((char *)str)[i]);
}

static void	putstrn_wchart(const void *str, int len)
{
	int			i;

	i = -1;
	while (++i < len)
		fputwchar(((wchar_t *)str)[i]);
}

static void
	handle_size(const void *str, enum e_size size, t_fputstrn *fptr, int *lptr)
{
	int	len;

	len = -1;
	if (size != SIZE_L)
	{
		*lptr = ft_strlen((char *)str);
		*fptr = &putstrn_char;
		return ;
	}
	while (((wchar_t *)str)[len])
		len++;
	*lptr = len;
	*fptr = &putstrn_wchart;
}

static const void
	*get_vaarg(va_list *arg, enum e_size size, const char *nullstr)
{
	const char	*v;

	if (size == SIZE_L)
		v = (const char *)va_arg(*arg, wchar_t *);
	else
		v = va_arg(*arg, char *);
	if (!v)
		return (nullstr);
	return (v);
}

void	ft_fstr(va_list *arg, t_fspec *spec)
{
	const char	nullstr[] = "(null)";
	const char	*v = get_vaarg(arg, spec->size, nullstr);
	t_fputstrn	fputstrn;
	int			len;

	handle_size(v, spec->size, &fputstrn, &len);
	if (spec->precision != -1 && len > spec->precision)
		len = spec->precision;
	fjustify(0, spec, len);
	(*fputstrn)(v, len);
	fjustify(1, spec, len);
}
