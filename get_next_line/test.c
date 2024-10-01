/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:07:40 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/30 19:19:47 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#ifndef MAXLINES
# define MAXLINES 10
#endif

int	main(int argc, char **argv)
{
	int		fd;
	int		li;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("open error: %s\n", argv[1]);
		return (1);
	}
	li = 1;
	while (li <= MAXLINES && (line = get_next_line(fd)))
	{
		printf("line %d: %s\n", li, line);
		free(line);
	}
	if (li == MAXLINES && line)
		printf("...\nends after line %d\n", MAXLINES);
	else
		printf("ended at line %d\n", li);
}
