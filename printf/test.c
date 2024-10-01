/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:53:34 by kcsajka           #+#    #+#             */
/*   Updated: 2024/09/29 18:42:14 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ft_printf.h"
#include "ft_utils.h"
#include "ft_formats.h"
#include <string.h>
#include <limits.h>

#define FORMAT "%13p\n%-8.4u%5.8s\n%-8.4x%8.4X\n"
#define   VARS v, 42, "forty two", 4200, 50230

int	main(void)
{
	char *v = strdup("hello");
	ft_printf(FORMAT, VARS);
	printf(FORMAT, VARS);
	//ft_printf("string: \"%s\"\nchar: '%c'\nint: %d / %i\nhexl: %x\nhexu: %X\n\n", "hello", '4', 42, -24, 127, 432);
	//printf("string: \"%s\"\nchar: '%c'\nint: %d / %i\nhexl: %x\nhexu: %X\n", "hello", '4', 42, -24, 127, 432);
	//printf("d: .%-5.3d.\n", 2);
	//printf("s: .%s.\n", "");
	//printf("s: .%s.\n", (char *)0);
	//printf("c: .%c.\n", 0);
}
