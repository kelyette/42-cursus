/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                                 ) . . (      */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 02:29:40 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/08 18:58:42 by kcsajka                     /| | | |\    */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_formats.h"

int	put_format(va_list *value, const char **format)
{
	t_format_spec	spec;

	ft_bzero(&spec, sizeof(spec));
	spec.width = -1;
	spec.precision = -1;
	if (!spec_expect_all(value, format, &spec) || !(*spec.func)(value, &spec))
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	values;

	va_start(values, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!put_format(&values, &format))
			{
				printf("formatting error\n");
				return (-1);
			}
		}
		else
			ft_putchar_fd(*format++, 1);
	}
	va_end(values);
	return (0);
}
