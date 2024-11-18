/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:30:30 by kcsajka           #+#    #+#             */
/*   Updated: 2024/11/03 15:40:43 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
// limit for "width" and "precision" specifier values
// 0 means no limit
# ifndef ULIMIT
#  define ULIMIT 0
# endif
# include <stdarg.h>

int	g_char_count;
int	ft_printf(const char *format, ...);

#endif
