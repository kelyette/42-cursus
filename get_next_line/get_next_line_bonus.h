/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:11:16 by kcsajka           #+#    #+#             */
/*   Updated: 2024/12/16 16:30:36 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# ifndef FILE_MAX
#  define FILE_MAX 64
# endif

typedef struct s_pbuf
{
	char	*buf;
	size_t	start;
	size_t	end;
}	t_pbuf;

char	*get_next_line(int fd);
int		free_pbuf(t_pbuf *pbuf);
int		ft_strlen(char *s);
void	*ft_memchr(const void *s, int c, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif
