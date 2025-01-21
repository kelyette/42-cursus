/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:22 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/20 19:17:25 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#ifdef __linux__
# define PTRNULL "(nil)"
# define PTRNLEN 5
# define WIDTHPTR 0
#else
# define PTRNULL "0x0"
# define PTRNLEN 1
# define WIDTHPTR 1
#endif

static void	fputptr(uintptr_t p)
{
	if (p < 16)
	{
		fputstr("0x");
		fputchar(digitc((long)p, 0));
		return ;
	}
	fputptr(p / 16);
	fputchar(digitc((long)(p % 16), 0));
}

static int	uintptr_len(uintptr_t p)
{
	int	len;

	len = !p;
	while (p != 0 && ++len)
	{
		p /= 16;
	}
	return (len);
}

void	fmt_ptr(va_list *arg, t_fspec *spec)
{
	uintptr_t	ptr;
	int			len;

	ptr = (uintptr_t)va_arg(*arg, void *);
	len = uintptr_len(ptr);
	if (!ptr)
		len = PTRNLEN;
	if ((ptr || WIDTHPTR) && spec->width != -1)
		spec->width -= 2;
	if (spec->width != -1 && !spec->ljust)
		fpad(spec->width, len, spec->zpad);
	if (ptr)
		fputptr(ptr);
	else
		fputstr(PTRNULL);
	if (spec->width != -1 && spec->ljust)
		fpad(spec->width, len, 0);
}
