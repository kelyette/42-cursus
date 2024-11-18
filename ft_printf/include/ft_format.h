/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:09:59 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/04 15:45:15 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FORMAT_H
# define FT_FORMAT_H
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

# define CASEOFFSET -32

struct						s_fspec;
typedef void				(*t_ffptr)(va_list *, struct s_fspec *);
typedef long long			t_llong;
typedef unsigned long long	t_ullong;

typedef struct s_fspec
{
	int		width;
	int		precision;
	int		ljust;
	int		psign;
	int		fillsign;
	int		hexprefix;
	int		zpad;
	int		size;
	char	spec;
	t_ffptr	func;
}	t_fspec;

enum e_size
{
	SIZE_NONE,
	SIZE_HH,
	SIZE_H,
	SIZE_L,
	SIZE_LL
};

// parser functions
int		expect_flags(const char **format, t_fspec *spec);
int		expect_width(va_list *arg, const char **format, t_fspec *spec);
int		expect_precision(va_list *arg, const char **format, t_fspec *spec);
int		expect_length(const char **format, t_fspec *spec);
int		expect_specifier(const char **format, t_fspec *spec);

int		spec_parse(va_list *arg, const char **format, t_fspec *spec);
void	spec_parse_post(t_fspec *spec);

// handler functions
void	ft_fchar(va_list *arg, t_fspec *spec);
void	ft_fstr(va_list *arg, t_fspec *spec);
void	ft_fint(va_list *arg, t_fspec *spec);
void	ft_fuint(va_list *arg, t_fspec *spec);
void	ft_ffloat(va_list *arg, t_fspec *spec);
void	ft_counter(va_list *arg, t_fspec *spec);

// printer functions
void	fputchar(char c);
void	fjustify(int after, const t_fspec *spec, int len);

// utility functions
void	get_zpad_int(const t_fspec *spec, int *zpad, int *absolute);
#endif
