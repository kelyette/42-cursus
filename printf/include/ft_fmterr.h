/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmterr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:02:19 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 17:05:44 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FMTERR_H
# define FT_FMTERR_H

enum e_fmterr
{
	FE_UFLAG,
	FE_INCFLAG,
	FE_USPEC,
	FE_BADNUM,
};

enum e_fmterr	g_fmterrno;

void	fmterr(enum e_fmterr errno, const char *s, size_t len)
{
	ft_putstr_fd("ft_printf");
}

#endif
