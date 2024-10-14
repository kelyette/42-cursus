/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.h                                                ) . . (      */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 03:09:59 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/14 00:13:50 by kcsajka                     /| | | |\    */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FORMATS_H
# define FT_FORMATS_H
# include <stdarg.h>
# include <stdlib.h>
# define ZPADOFFSET 16

struct			s_format_spec;
typedef size_t	(*t_ffptr)(va_list *, const struct s_format_spec *);
typedef void	(*t_fwrap)(void);

typedef enum e_flags
{
	NIL_FLAG,
	LJUST,
	LPAD,
}	t_flags;

typedef struct s_format_spec
{
	int		width;
	int		precision;
	int		ljust;
	int		zpad;
	int		hexprefix;
	t_ffptr	func;
}	t_format_spec;

typedef struct s_spec_array
{
	t_format_spec	*arr;
	size_t			size;
}	t_spec_array;

int		spec_expect_all(va_list *arg, const char **fmtstr, t_format_spec *spec);

int		put_format(va_list *v, const char **f);
// format printer functions
size_t	ft_fputchar(va_list *arg, const t_format_spec *spec);
size_t	ft_fputstr(va_list *arg, const t_format_spec *spec);
size_t	ft_fputint(va_list *arg, const t_format_spec *spec);
size_t	ft_fputuint(va_list *arg, const t_format_spec *spec);
size_t	ft_fputhexlow(va_list *arg, const t_format_spec *spec);
size_t	ft_fputhexup(va_list *arg, const t_format_spec *spec);
size_t	ft_fputpointer(va_list *arg, const t_format_spec *spec);
size_t	ft_fputliteral(va_list *arg, const t_format_spec *spec);
// format utils
void	justify(const t_format_spec *spec, int len);
void	pad_zero(const t_format_spec *spec, size_t len);
#endif
