/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:22:35 by kcsajka           #+#    #+#             */
/*   Updated: 2024/10/02 12:50:58 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

typedef struct s_pbuf
{
	char	*buf;
	size_t	start;
	size_t	end;
}	t_pbuf;

char	*get_next_line(int fd);
int		ft_strlen(char *s);
void	*ft_memchr(const void *s, int c, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t size);
void	*ft_realloc(void *s, size_t bsize, size_t nsize);
void	*ft_calloc(size_t count, size_t size);

#endif
