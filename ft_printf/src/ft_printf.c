/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 02:29:40 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 17:59:05 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_formats.h"

int	put_format(va_list *value, const char **format)
{
	t_format_spec	spec;
	size_t			tmp;

	ft_bzero(&spec, sizeof(spec));
	tmp = spec_expect_all(value, format, &spec);
	if (!tmp || !(*spec.func)(value, &spec))
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