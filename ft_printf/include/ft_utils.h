/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:21:06 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 02:45:28 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H
# include <stdlib.h>

long	max(long a, long b);
long	min(long a, long b);
char	hex_val(int n, int ucase);
size_t	get_length_base(long n, int base);

#endif
