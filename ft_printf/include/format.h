/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:09:59 by kcsajka           #+#    #+#             */
/*   Updated: 2025/01/22 14:18:14 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H
# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>
# include <limits.h>

// limit for "width" and "precision" specifier values
// 0 means no limit
# ifndef ULIMIT
#  define ULIMIT 0
# endif

struct			s_fspec;
typedef int	(*t_ffptr)(va_list *, struct s_fspec *);

extern int		g_char_count;

typedef struct s_fspec
{
	int		width;
	int		precision;
	int		ljust;
	int		psign;
	int		fillsign;
	int		hexprefix;
	int		zpad;
	char	spec;
	t_ffptr	func;
}	t_fspec;

typedef struct s_number
{
	long	n;
	char	fsign;
	char	pre[3];
	char	str[20];
	int		base;
	int		len;
	int		tlen;
	int		neg;
}	t_num;

// parser functions
int		expect_flags(const char **format, t_fspec *spec);
int		expect_width(va_list *arg, const char **format, t_fspec *spec);
int		expect_precision(va_list *arg, const char **format, t_fspec *spec);
int		expect_specifier(const char **format, t_fspec *spec);
int		spec_parse(va_list *arg, const char **format, t_fspec *spec);

// handler functions
int		fmt_int(va_list *arg, t_fspec *spec);
int		fmt_str(va_list *arg, t_fspec *spec);
int		fmt_char(va_list *arg, t_fspec *spec);
int		fmt_ptr(va_list *arg, t_fspec *spec);

// printer functions
int		fputchar(char c);
int		fputstr(const char *str);

// utility functions
int		ltoa_raw(char *dest, long n, int base, int ucase);
char	digitc(long n, int ucase);
int		fpad(int width, int len, int zpad);
#endif
